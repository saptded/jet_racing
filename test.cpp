#include "gtest/gtest.h"
#include "utils.hpp"
#include "cmath"

#include "drawableArc.hpp"
namespace gtest{

DrawableArc arc;
float xc = 200, yc = 200;
float sin = 25;
float cos = 43.301272; // при радиусе 50
Point centre {xc,yc};

Point first {xc+cos, yc-sin};
Point second {xc-sin, yc-cos};
Point third {xc-sin, yc+cos};
Point fourth {xc+cos, yc+sin};

Point right {xc+50, yc};
Point top {xc, yc-50};
Point left {xc-50, yc};
Point bottom {xc,yc+50};

Point ms {350,550};
Point me{400,600};
Point mc {400,550};


TEST(drawableArc, getAngleCustom) {
    ASSERT_FLOAT_EQ(arc.getAngle(centre,second)/M_PI*180, 60);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,first)/M_PI*180, 150);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,fourth)/M_PI*180, 210);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,third)/M_PI*180, 300);
    ASSERT_FLOAT_EQ(arc.getAngle(mc,ms)/M_PI*180, 0);
    ASSERT_FLOAT_EQ(arc.getAngle(mc,me)/M_PI*180, 270);
}

TEST(drawableArc, getAngleQwadro) {
    ASSERT_FLOAT_EQ(arc.getAngle(centre,left)/M_PI*180, 0);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,top)/M_PI*180, 90);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,right)/M_PI*180, 180);
    ASSERT_FLOAT_EQ(arc.getAngle(centre,bottom)/M_PI*180, 270);
}
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}