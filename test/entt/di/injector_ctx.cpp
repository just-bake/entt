#include <gtest/gtest.h>
#include <entt/di/injector_ctx.hpp>
#include <entt/meta/factory.hpp>

struct clazz {
    clazz(int test) {}
    clazz(int test, int test2) {}
};

struct InjectorCtx: ::testing::Test {
    void SetUp() override {
        using namespace entt::literals;

        entt::meta_reset();
        entt::meta_factory<clazz>{}
            .type("clazz"_hs)
            .ctor<int>(1)
            .ctor<int, int>(0);
    }

    void TearDown() override {
        entt::meta_reset();
    }
};

TEST_F(InjectorCtx, CtorPriority) {
    using namespace entt::literals;

    auto type = entt::resolve("clazz"_hs);

    // Test boolean operator
    auto valid_ctor = type.ctor(0);

    ASSERT_TRUE(valid_ctor);
    ASSERT_EQ(valid_ctor.injection().ctor_priority(), 0);
}


TEST_F(InjectorCtx, CtorPrioritySorted) {
    using namespace entt::literals;

    auto type = entt::resolve("clazz"_hs);

    // Get all constructors
    auto ctors = type.ctor();

    int last_priority = -1;
    bool first = true;

    // Check that priorities are in ascending order
    for(auto curr: ctors) {
        auto current_priority = curr.second.injection().ctor_priority();
        if (first) {
            last_priority = current_priority;
            first = false;
            continue;
        }

        // Each subsequent constructor should have a priority greater than or equal to the last one
        ASSERT_GE(current_priority, last_priority);
        last_priority = current_priority;
    }
}