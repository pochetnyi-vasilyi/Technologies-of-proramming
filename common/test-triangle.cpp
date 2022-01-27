#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "triangle.hpp"
#include "base-types.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(triangle_constructor)

BOOST_AUTO_TEST_CASE(triangle_constructor_center_frame_rect_correctness)
{
  const pochetnyi::point_t a = { 0.0, 0.0 };
  const pochetnyi::point_t b = { 1.0, 0.0 };
  const pochetnyi::point_t c = { 0.0, 1.0 };
  BOOST_CHECK_NO_THROW(pochetnyi::Triangle triang(a, b, c));
  pochetnyi::Triangle triang( a, b, c );
  BOOST_CHECK_CLOSE(triang.getCenter().x, (a.x + b.x + c.x) / 3.0, delta);
  BOOST_CHECK_CLOSE(triang.getCenter().y, (a.y + b.y + c.y) / 3.0, delta);
  BOOST_CHECK_CLOSE(triang.getFrameRect().width, std::max({a.x, b.x, c.x}) - std::min({a.x, b.x, c.x}), delta);
  BOOST_CHECK_CLOSE(triang.getFrameRect().height, std::max({a.y, b.y, c.y}) - std::min({a.y, b.y, c.y}), delta);
}

BOOST_AUTO_TEST_CASE(triangle_constructor_points_on_line_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Triangle triang({ 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }), std::invalid_argument);
  BOOST_CHECK_THROW(pochetnyi::Triangle triang({ 0.0, 0.0 }, { -2.0, 0.0 }, { 2.0, 0.0 }), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_move)

BOOST_AUTO_TEST_CASE(triangle_move_to_point_center_correctness)
{
  pochetnyi::Triangle triang({ 5.0, 5.0 }, { 1.0, 20.0 }, { 6.0, -4.0 });
  const pochetnyi::point_t point{ 31.0, 59.0 };
  triang.move(point);
  BOOST_CHECK_EQUAL(triang.getCenter().x, point.x);
  BOOST_CHECK_EQUAL(triang.getCenter().y, point.y);
}

BOOST_AUTO_TEST_CASE(triangle_move_by_delta_center_correctness)
{
  const pochetnyi::point_t a = { 0.0, 0.0 };
  const pochetnyi::point_t b = { 10.0, 3.0 };
  const pochetnyi::point_t c = { 3.0, 10.0 };
  pochetnyi::Triangle triang(a, b, c);
  const double dx = 13.0;
  const double dy = 68.0;
  triang.move(dx, dy);
  BOOST_CHECK_CLOSE(triang.getCenter().x, (a.x + b.x + c.x) / 3.0 + dx, delta);
  BOOST_CHECK_CLOSE(triang.getCenter().y, (a.y + b.y + c.y) / 3.0 + dy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_scale)

BOOST_AUTO_TEST_CASE(triangle_scale_less_or_equal_zero_coefficient_exception_throw)
{
  pochetnyi::Triangle triang({ -10.0, -17.0 }, { 11.0, 47.0 }, { -46.0, 82.0 });
  BOOST_CHECK_THROW(triang.scale(-28.0), std::invalid_argument);
  BOOST_CHECK_THROW(triang.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(triangle_scale_center_frame_rect_correctness)
{
  const pochetnyi::point_t a = { 25.0, 0.0 };
  const pochetnyi::point_t b = { 11.0, 3.0 };
  const pochetnyi::point_t c = { 3.0, 10.0 };
  pochetnyi::Triangle triang(a, b, c);
  const double coef = 17.0;
  triang.scale(coef);
  BOOST_CHECK_CLOSE(triang.getFrameRect().width, (std::max({a.x, b.x, c.x})
      - std::min({a.x, b.x, c.x})) * coef, delta);
  BOOST_CHECK_CLOSE(triang.getFrameRect().height, (std::max({a.y, b.y, c.y})
      - std::min({a.y, b.y, c.y})) * coef, delta);
  BOOST_CHECK_CLOSE(triang.getCenter().x, (a.x + b.x + c.x) / 3.0, delta);
  BOOST_CHECK_CLOSE(triang.getCenter().y, (a.y + b.y + c.y) / 3.0, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_rotate)

BOOST_AUTO_TEST_CASE(triangle_rotate_center_frame_rect_correctness)
{
  const pochetnyi::point_t a = { 15.0, 0.0 };
  const pochetnyi::point_t b = { 14.0, 33.0 };
  const pochetnyi::point_t c = { 13.0, 10.0 };
  pochetnyi::Triangle triang(a, b, c);
  const double degrees = 720.0;
  const double width = triang.getFrameRect().width;
  const double height = triang.getFrameRect().height;
  triang.rotate(degrees);
  BOOST_CHECK_CLOSE(triang.getCenter().x, (a.x + b.x + c.x) / 3.0, delta);
  BOOST_CHECK_CLOSE(triang.getCenter().y, (a.y + b.y + c.y) / 3.0, delta);
  BOOST_CHECK_CLOSE(triang.getFrameRect().width, width, delta);
  BOOST_CHECK_CLOSE(triang.getFrameRect().height, height, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(triangle_area)

BOOST_AUTO_TEST_CASE(triangle_move_to_point_returns_equal_area)
{
  pochetnyi::Triangle triang({ 41.002, 67.93 }, { 94.555, 2.999 }, { -11.871, -25.18 });
  double area = triang.getArea();
  const pochetnyi::point_t point{ -16.0, 58.0 };
  triang.move(point);
  BOOST_CHECK_CLOSE(triang.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(triangle_move_by_delta_returns_equal_area)
{
  pochetnyi::Triangle triang({ 20.12, 0.435 }, { 14.11, 3.696 }, { 2.59, 9.91 });
  double area = triang.getArea();
  const double dx = 35.0;
  const double dy = 97.0;
  triang.move(dx, dy);
  BOOST_CHECK_CLOSE(triang.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(triangle_scale_area_correctness)
{
  pochetnyi::Triangle triang({ 17.18, 19.538 }, { -11.42, 6.47 }, { 18.11, -35.016 });
  double area = triang.getArea();
  const double coef = 15.0;
  triang.scale(coef);
  BOOST_CHECK_CLOSE(triang.getArea(), area * coef * coef, delta);
}

BOOST_AUTO_TEST_CASE(triangle_rotate_area_correctness)
{
  pochetnyi::Triangle triang({ 16.0, 21.0 }, { -14.0, 13.0 }, { 15.0, -46.0 });
  double area = triang.getArea();
  const double degrees = 180.0;
  triang.rotate(degrees);
  BOOST_CHECK_CLOSE(triang.getArea(), area, delta);
}

BOOST_AUTO_TEST_SUITE_END()
