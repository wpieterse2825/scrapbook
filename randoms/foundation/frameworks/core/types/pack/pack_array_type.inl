namespace next_mode::core::types::detail {
    template <typename ElementType, int Width>
    struct PackArrayType {
        // TODO(wpieterse): Fix this!
        using Type = std::array<ElementType, Width>;
    };
} // namespace next_mode::core::types::detail
