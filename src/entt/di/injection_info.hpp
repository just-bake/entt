#ifndef ENTT_DI_INJECTION_INFO_HPP
#define ENTT_DI_INJECTION_INFO_HPP

#include "../core/attribute.h"
#include "../core/type_traits.hpp"

namespace entt::di {
/*! @brief Information about dependency injection requirements. */
struct ENTT_API injection_info final {
    /**
     * @brief Constructs injection info for a constructor.
     * @param prio Priority of this constructor for injection (lower number = higher priority).
     */
    explicit constexpr injection_info(const int prio) noexcept
        : priority{prio},
          optional_dep{false},
          has_injection_id{false},
          should_inject{true},
          injection_id{} {}

    /**
     * @brief Constructs injection info for a data member or function parameter.
     * @param opt Whether this is an optional dependency.
     * @param id Optional injection identifier.
     */
    explicit constexpr injection_info(const bool opt = false, const id_type id = id_type{}) noexcept
        : priority{0},
          optional_dep{opt},
          has_injection_id{id != id_type{}},
          should_inject{true},
          injection_id{id} {}

    /**
     * @brief Returns the constructor priority.
     * @return Constructor priority value.
     */
    [[nodiscard]] constexpr int ctor_priority() const noexcept {
        return priority;
    }

    /**
     * @brief Checks if the dependency is optional.
     * @return True if the dependency is optional, false otherwise.
     */
    [[nodiscard]] constexpr bool is_optional() const noexcept {
        return optional_dep;
    }

    /**
     * @brief Checks if an injection ID is specified.
     * @return True if an injection ID is specified, false otherwise.
     */
    [[nodiscard]] constexpr bool has_id() const noexcept {
        return has_injection_id;
    }

    /**
     * @brief Returns the injection identifier.
     * @return The injection identifier if specified.
     */
    [[nodiscard]] constexpr id_type id() const noexcept {
        return injection_id;
    }

    /**
     * @brief Returns false if a wrapper is invalid, true otherwise.
     * @return False if the wrapper is invalid, true otherwise.
     */
    [[nodiscard]] explicit operator bool() const noexcept {
        return should_inject;
    }

private:
    int priority;
    bool optional_dep;
    bool has_injection_id;
    bool should_inject;
    id_type injection_id;
};

} // namespace entt::di

#endif // ENTT_DI_INJECTION_INFO_HPP
