#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "polygon.hpp"
#include "base-types.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(polygon_constructor)

BOOST_AUTO_TEST_CASE(polygon_constructor_vertexes_correctness)
{
  BOOST_CHECK_NO_THROW(pochetnyi::Polygon({ { 13.0, 22.0 }, { 14.0, 5.0 }, { 3.0, -1.0 }, { 24.0, -9.0 } }));
  std::initializer_list<pochetnyi::point_t> points = { { 13.0, 22.0 }, { 14.0, 5.0 }, { 3.0, -1.0 }, { 24.0, -9.0 } };
  pochetnyi::Polygon poly(points);
  size_t i = 0;
  for(pochetnyi::point_t point : points)
  {
    BOOST_CHECK_EQUAL(poly[i].x, point.x);
    BOOST_CHECK_EQUAL(poly[i].y, point.y);
    i++;
  }
}

BOOST_AUTO_TEST_CASE(polygon_constructor_less_than_three_points_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Polygon({ { 13.62, 15.88 }, { 0.1456, 19.2 } }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_constructor_invalid_area_exception_throw)
{
  BOOST_CHECK_THROW(pochetnyi::Polygon({ { 0.0, 0.0 }, { 5.0, 0.0 }, { 9.0, 0.0 } }), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_move)

BOOST_AUTO_TEST_CASE(polygon_move_to_point_center_correctness)
{
  pochetnyi::Polygon poly({ { 2.0, 2.0 }, { 5.0, 7.0 }, { 32.0, 10.0 }, { 16.0, -19.0 } });
  const pochetnyi::point_t point{ 75.0, 63.0 };
  poly.move(point);
  BOOST_CHECK_CLOSE(poly.getCenter().x, point.x, delta);
  BOOST_CHECK_CLOSE(poly.getCenter().y, point.y, delta);
}

BOOST_AUTO_TEST_CASE(polygon_move_by_delta_center_correctness)
{
  pochetnyi::Polygon poly({ { 0.0, 0.0 }, { 6.0, 6.0 }, { -3.0, 3.0 }, { 3.0, 3.0 }, { 3.0, 0.0 } });
  const pochetnyi::point_t center = poly.getCenter();
  const double dx = 14.0;
  const double dy = 28.0;
  poly.move(dx, dy);
  BOOST_CHECK_CLOSE(poly.getCenter().x, center.x + dx, delta);
  BOOST_CHECK_CLOSE(poly.getCenter().y, center.y + dy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_scale)

BOOST_AUTO_TEST_CASE(polygon_scale_less_or_equal_zero_coefficient_exception_throw)
{
  pochetnyi::Polygon poly({ { 18.57, -15.6 }, { 76.99, 116.2 }, { -31.05, 83.65 }, { 54.37, 3.025 } });
  BOOST_CHECK_THROW(poly.scale(-2.0), std::invalid_argument);
  BOOST_CHECK_THROW(poly.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_scale_center_frame_rect_correctness)
{
  pochetnyi::Polygon poly({ { -19.46, 82.11 }, { 7.8, 35.6 }, { -14.78, 41.32 }, { 61.09, 23.91 } });
  const pochetnyi::point_t center = poly.getCenter();
  const pochetnyi::rectangle_t frameRect = poly.getFrameRect();
  const double coef = 6.0;
  poly.scale(coef);
  BOOST_CHECK_CLOSE(poly.getFrameRect().width, frameRect.width * coef, delta);
  BOOST_CHECK_CLOSE(poly.getFrameRect().height, frameRect.height * coef, delta);
  BOOST_CHECK_CLOSE(poly.getCenter().x, center.x, delta);
  BOOST_CHECK_CLOSE(poly.getCenter().y, center.y, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_rotate)

BOOST_AUTO_TEST_CASE(polygon_rotate_center_frame_rect_correctness)
{
  pochetnyi::Polygon poly({ { 15.0, 1.0 }, { 20.0, 7.0 }, { 25.0, -4.0 }, { 30.0, -7.0 } });
  const pochetnyi::point_t center = poly.getCenter();
  const pochetnyi::rectangle_t frameRect = poly.getFrameRect();
  const double degrees = 180.0;
  poly.rotate(degrees);
  BOOST_CHECK_CLOSE(poly.getCenter().x, center.x, delta);
  BOOST_CHECK_CLOSE(poly.getCenter().y, center.y, delta);
  BOOST_CHECK_CLOSE(poly.getFrameRect().width, frameRect.width, delta);
  BOOST_CHECK_CLOSE(poly.getFrameRect().height, frameRect.height, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(polygon_area)

BOOST_AUTO_TEST_CASE(polygon_move_to_point_returns_equal_area)
{
  pochetnyi::Polygon poly({ { 13.0, 22.0 }, { 14.0, 5.0 }, { 37.0, -14.0 }, { 3.0, -1.0 }, { 24.0, -9.0 } });
  const double area = poly.getArea();
  const pochetnyi::point_t point{ 5.0, 3.0 };
  poly.move(point);
  BOOST_CHECK_CLOSE(poly.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(polygon_move_by_delta_returns_equal_area)
{
  pochetnyi::Polygon poly({ { 48.0, 19.0 }, { 39.0, -7.0 }, { 56.0, -45.0 }, { 74.0, 72.0 } });
  const double area = poly.getArea();
  const double dx = 4.0;
  const double dy = 8.0;
  poly.move(dx, dy);
  BOOST_CHECK_CLOSE(poly.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(polygon_scale_area_correctness)
{
  pochetnyi::Polygon poly({ { 10.0, 0.0 }, { 20.0, 70.0 }, { 0.0, 40.0 } });
  const double area = poly.getArea();
  const double coef = 10.0;
  poly.scale(coef);
  BOOST_CHECK_CLOSE(poly.getArea(), area * coef * coef, delta);
}

BOOST_AUTO_TEST_CASE(polygon_rotate_area_correctness)
{
  pochetnyi::Polygon poly({ { 35.0, 16.0 }, { 9.0, -7.0 }, { 33.0, -45.0 }, { 12.0, 8.0 } });
  const double area = poly.getArea();
  const double degrees = 110.0;
  poly.rotate(degrees);
  BOOST_CHECK_CLOSE(poly.getArea(), area, delta);
}

BOOST_AUTO_TEST_SUITE_END()
