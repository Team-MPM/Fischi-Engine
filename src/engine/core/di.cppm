export module core:di;

import :service;
import std;

// ReSharper disable CppFunctionIsNotImplemented

template<typename T>
auto has_dependencies_impl(int) -> decltype(typename T::Dependencies{}, std::true_type{});
template<typename T>
std::false_type has_dependencies_impl(...);

template<typename T>
constexpr bool has_dependencies = decltype(has_dependencies_impl<T>(0))::value;

template<typename T, typename Container>
std::unique_ptr<T> createInstanceImpl(Container& container) {
    if constexpr(has_dependencies<T>) {
        using Deps = typename T::Dependencies;
        return createInstanceWithDependencies<T, Deps>(container);
    } else {
        return std::make_unique<T>();
    }
}

template<typename T, typename Tuple, std::size_t... I, typename Container>
std::unique_ptr<T> createInstanceWithDependenciesImpl(Container& container, std::index_sequence<I...>) {
    return std::make_unique<T>(container.template resolve<std::tuple_element_t<I, Tuple>>()...);
}

template<typename T, typename Tuple, typename Container>
std::unique_ptr<T> createInstanceWithDependencies(Container& container) {
    return createInstanceWithDependenciesImpl<T, Tuple>(container, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

export class DIContainer {
public:
    template<typename ServiceType>
    ServiceType* resolve() {
        const std::type_index key(typeid(ServiceType));
        if (const auto it = m_ServiceInstances.find(key); it != m_ServiceInstances.end())
            return static_cast<ServiceType*>(it->second.get());
        auto instance = createInstanceImpl<ServiceType>(*this);
        ServiceType* rawPtr = instance.get();
        m_ServiceInstances[key] = std::move(instance);
        return rawPtr;
    }
private:
    std::unordered_map<std::type_index, std::unique_ptr<IService>> m_ServiceInstances;
};