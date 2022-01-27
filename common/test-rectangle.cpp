#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(rectangle_constructor)

BOOST_AUTO_TEST_CASE(rectangle_constructor_center_frame_rect_correctness)
{
  const double width = 5.0;
  const double height = 7.0;
  const pochetnyi::point_t center = { 2.0, 2.0 };
  BOOST_CHECK_NO_THROW(pochetnyi::Rectangle rect(center, width, height));
  pochetnyi::Rectangle rect(center, width, height);
  BOOST_CHECK_EQUAL(rect.getFrameRect().width, width);
  BOOST_CHECK_EQUAL(rect.getFrameRect().height, height);
  BOOST_CHECK_EQUAL(rect.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(rect.getCenter().y, center.y);
}

BOOST_AUTO_TEST_CASE(rectangle_constructor_width_less_or_equal_zero_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Rectangle rect({ 0.0, 0.0 }, -3.0, 5.0), std::invalid_argument);
  BOOST_CHECK_THROW(pochetnyi::Rectangle rect({ 6.0, 2.0 }, 0.0, 12.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_constructor_height_less_or_equal_zero_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Rectangle rect({ 9.0, 16.0 }, 3.0, -5.0), std::invalid_argument);
  BOOST_CHECK_THROW(pochetnyi::Rectangle rect({ 3.0, 8.0 }, 12.0, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_move)

BOOST_AUTO_TEST_CASE(rectangle_move_to_point_center_correctness)
{
  pochetnyi::Rectangle rect({ 2.0, 2.0 }, 5.0, 7.0);
  const pochetnyi::point_t point{ 36.0, 55.0 };
  rect.move(point);
  BOOST_CHECK_EQUAL(rect.getCenter().x, point.x);
  BOOST_CHECK_EQUAL(rect.getCenter().y, point.y);
}

BOOST_AUTO_TEST_CASE(rectangle_move_by_delta_center_correctness)
{
  const pochetnyi::point_t center = { 10.0, 20.0 };
  pochetnyi::Rectangle rect(center, 98.0, 71.0);
  const double dx = 73.0;
  const double dy = 6.0;
  rect.move(dx, dy);
  BOOST_CHECK_CLOSE(rect.getCenter().x, center.x + dx, delta);
  BOOST_CHECK_CLOSE(rect.getCenter().y, center.y + dy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_scale)

BOOST_AUTO_TEST_CASE(rectangle_scale_less_or_equal_zero_coefficient_exception_throw)
{
  pochetnyi::Rectangle rect({ 15.0, 23.0 }, 11.0, 33.0);
  BOOST_CHECK_THROW(rect.scale(-2.0), std::invalid_argument);
  BOOST_CHECK_THROW(rect.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_scale_center_frame_rect_correctness)
{
  const double width = 16.0;
  const double height = 41.0;
  const pochetnyi::point_t center = { 92.0, 0.0 };
  pochetnyi::Rectangle rect(center, width, height);
  const double coef = 6.0;
  rect.scale(coef);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, width * coef, delta);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, height * coef, delta);
  BOOST_CHECK_EQUAL(rect.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(rect.getCenter().y, center.y);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_rotate)

BOOST_AUTO_TEST_CASE(rectangle_rotate_center_frame_rect_correctness)
{
  const double width = 65.0;
  const double height = 74.0;
  const pochetnyi::point_t center = { -55.0, 0.0 };
  pochetnyi::Rectangle rect(center, width, height);
  const double degrees = 365.0;
  rect.rotate(degrees);
  BOOST_CHECK_EQUAL(rect.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(rect.getCenter().y, center.y);
  const double rads = degrees * (M_PI / 180.0);
  const double frWidth = height * fabs(sin(rads)) + width * fabs(cos(rads));
  const double frHeight = height * fabs(cos(rads)) + width * fabs(sin(rads));
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, frWidth, delta);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, frHeight, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangle_area)

BOOST_AUTO_TEST_CASE(rectangle_constructor_area_correctness)
{
  const double width = 19.0;
  const double height = 13.0;
  pochetnyi::Rectangle rect({ 7.0, 77.0 }, width, height);
  BOOST_CHECK_CLOSE(rect.getArea(), width * height, delta);
}

BOOST_AUTO_TEST_CASE(rectangle_move_to_point_returns_equal_area)
{
  const double width = 32.0;
  const double height = 76.0;
  pochetnyi::Rectangle rect({ 51.0, 10.0 }, width, height);
  const pochetnyi::point_t point{ 5.0, 3.0 };
  rect.move(point);
  BOOST_CHECK_CLOSE(rect.getArea(), width * height, delta);
}

BOOST_AUTO_TEST_CASE(rectangle_move_by_delta_returns_equal_area)
{
  const double width = 45.0;
  const double height = 67.0;
  pochetnyi::Rectangle rect({ 12.0, 14.0 }, width, height);
  const double dx = 4.0;
  const double dy = 8.0;
  rect.move(dx, dy);
  BOOST_CHECK_CLOSE(rect.getArea(), width * height, delta);
}

BOOST_AUTO_TEST_CASE(rectangle_scale_area_correctness)
{
  const double width = 64.0;
  const double height = 54.0;
  pochetnyi::Rectangle rect({ 0.0, 0.0 }, width, height);
  const double coef = 10.0;
  rect.scale(coef);
  const double area = width * height * coef * coef;
  BOOST_CHECK_CLOSE(rect.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(rectangle_rotate_area_correctness)
{
  const double width = 33.0;
  const double height = 96.0;
  pochetnyi::Rectangle rect({ 71.0, 8.0 }, width, height);
  const double degrees = 110.0;
  rect.rotate(degrees);
  BOOST_CHECK_CLOSE(rect.getArea(), width * height, delta);
}

BOOST_AUTO_TEST_SUITE_END()
