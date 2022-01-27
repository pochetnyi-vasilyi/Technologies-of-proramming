#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(circle_constructor)

BOOST_AUTO_TEST_CASE(circle_constructor_center_radius_frame_rect_correctness)
{
  const double radius = 5.0;
  const pochetnyi::point_t center = { 0.0, 2.0 };
  BOOST_CHECK_NO_THROW(pochetnyi::Circle circ(center, radius));
  pochetnyi::Circle circ(center, radius);
  BOOST_CHECK_EQUAL(circ.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(circ.getCenter().y, center.y);
  BOOST_CHECK_EQUAL(circ.getRadius(), radius);
  BOOST_CHECK_EQUAL(circ.getFrameRect().width, radius * 2.0);
  BOOST_CHECK_EQUAL(circ.getFrameRect().height, radius * 2.0);
}

BOOST_AUTO_TEST_CASE(circle_constructor_radius_less_or_equal_zero_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Circle circ({ 10.0, 0.0 }, -1.0), std::invalid_argument);
  BOOST_CHECK_THROW(pochetnyi::Circle circ({ 10.0, 0.0 }, 0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_move)

BOOST_AUTO_TEST_CASE(circle_move_to_point_center_correctness)
{
  pochetnyi::Circle circ({ 11.0, 15.0 }, 25.0);
  const pochetnyi::point_t point{ 9.0, 50.0 };
  circ.move(point);
  BOOST_CHECK_EQUAL(circ.getCenter().x, point.x);
  BOOST_CHECK_EQUAL(circ.getCenter().y, point.y);
}

BOOST_AUTO_TEST_CASE(circle_move_by_delta_center_correctness)
{
  const pochetnyi::point_t center = { 65.0, 88.0 };
  pochetnyi::Circle circ(center, 5.0);
  const double dx = 5.0;
  const double dy = 12.0;
  circ.move(dx, dy);
  BOOST_CHECK_CLOSE(circ.getCenter().x, center.x + dx, delta);
  BOOST_CHECK_CLOSE(circ.getCenter().y, center.y + dy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_scale)

BOOST_AUTO_TEST_CASE(circle_scale_less_or_equal_zero_coefficient_exception_throw)
{
  pochetnyi::Circle circ({ 51.0, 83.0 }, 5.0);
  BOOST_CHECK_THROW(circ.scale(-25.0), std::invalid_argument);
  BOOST_CHECK_THROW(circ.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(circle_scale_center_frame_rect_radius_correctness)
{
  const double radius = 37.0;
  const pochetnyi::point_t center = { 65.0, 88.0 };
  pochetnyi::Circle circ(center, 37.0);
  const double coef = 4.0;
  circ.scale(coef);
  const double diameter = radius * coef * 2.0;
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, diameter, delta);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, diameter, delta);
  BOOST_CHECK_CLOSE(circ.getRadius(), radius * coef, delta);
  BOOST_CHECK_EQUAL(circ.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(circ.getCenter().y, center.y);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_rotate)

BOOST_AUTO_TEST_CASE(circle_rotate_center_frame_rect_correctness)
{
  const double radius = 18.0;
  const pochetnyi::point_t center = { 135.0, 11.0 };
  pochetnyi::Circle circ(center, radius);
  const double degrees = 711.0;
  const double width = circ.getFrameRect().width;
  const double height = circ.getFrameRect().height;
  circ.rotate(degrees);
  BOOST_CHECK_EQUAL(circ.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(circ.getCenter().y, center.y);
  BOOST_CHECK_EQUAL(circ.getFrameRect().width, width);
  BOOST_CHECK_EQUAL(circ.getFrameRect().height, height);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_area)

BOOST_AUTO_TEST_CASE(circle_constructor_area_correctness)
{
  const double radius = 91.0;
  pochetnyi::Circle circ({ 28.0, 39.0 }, radius);
  const double area = M_PI * radius * radius;
  BOOST_CHECK_CLOSE(circ.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(circle_area_after_move_to_point_returns_equal_area)
{
  const double radius = 9.0;
  pochetnyi::Circle circ({ 23.0, 32.0 }, radius);
  const pochetnyi::point_t point{ 32.0, 22.0 };
  circ.move(point);
  const double area = M_PI * radius * radius;
  BOOST_CHECK_CLOSE(circ.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(circle_area_after_move_by_delta_returns_equal_area)
{
  const double radius = 50.0;
  pochetnyi::Circle circ({ 2.0, 2.0 }, radius);
  const double dx = 44.0;
  const double dy = 77.0;
  circ.move(dx, dy);
  const double area = M_PI * radius * radius;
  BOOST_CHECK_CLOSE(circ.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(circle_scale_area_correctness)
{
  const double radius = 21.0;
  pochetnyi::Circle circ({ 30.0, 60.0 }, radius);
  const double coef = 3.0;
  circ.scale(coef);
  const double area = M_PI * radius * radius * coef * coef;
  BOOST_CHECK_CLOSE(circ.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(circle_rotate_area_correctness)
{
  const double radius = 37.0;
  pochetnyi::Circle circ({ 23.0, 78.0 }, radius);
  const double degrees = 125.0;
  circ.rotate(degrees);
  const double area = M_PI * radius * radius;
  BOOST_CHECK_CLOSE(circ.getArea(), area, delta);
}

BOOST_AUTO_TEST_SUITE_END()
