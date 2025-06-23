#include <gtest/gtest.h>
#include <entt/di/injector_ctx.hpp>

#include <entt/meta/factory.hpp>

struct clazz {
};

struct InjectorCtx: ::testing::Test {
    void SetUp() override {
        using namespace entt::literals;

        entt::meta_factory<clazz>{}
            .type("clazz"_hs);
    }
};

TEST_F(InjectorCtx, constructorSize) {
    ASSERT_TRUE(false);
}