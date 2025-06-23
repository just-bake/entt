#include <gtest/gtest.h>
#include <entt/di/injector_ctx.hpp>

#include <entt/meta/factory.hpp>

struct clazz {
    clazz(int test) {}
};

struct InjectorCtx: ::testing::Test {
    void SetUp() override {
        using namespace entt::literals;

        entt::meta_factory<clazz>{}
            .type("clazz"_hs)
            .ctor<int>();
    }
};

TEST_F(InjectorCtx, constructorSize) {
    auto type = entt::resolve<clazz>();

    ASSERT_EQ(type.ctor_count(), 1);
}