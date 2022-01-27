#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <cmath>
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(composite_shape_constructor)

BOOST_AUTO_TEST_CASE(composite_shape_constructor_center_frame_rect_count_correctness)
{
  const double width = 11.0;
  const double height = 12.0;
  const pochetnyi::point_t center = { 3.2, 6.5 };
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(center, width, height);
  BOOST_CHECK_NO_THROW(pochetnyi::CompositeShape cShape);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  BOOST_CHECK_EQUAL(cShape.getCenter().x, center.x);
  BOOST_CHECK_EQUAL(cShape.getCenter().y, center.y);
  BOOST_CHECK_EQUAL(cShape.getFrameRect().width, width);
  BOOST_CHECK_EQUAL(cShape.getFrameRect().height, height);
  BOOST_CHECK_EQUAL(cShape.getCount(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_move)

BOOST_AUTO_TEST_CASE(composite_shape_move_to_point_center_correctness)
{
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{0.0, 0.0}, 15.0);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{31.0, 28.0}, 13.0, 42.0);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(circ);
  cShape.addShape(rect);
  const pochetnyi::point_t point{ 9.0, 50.0 };
  cShape.move(point);
  BOOST_CHECK_EQUAL(cShape.getCenter().x, point.x);
  BOOST_CHECK_EQUAL(cShape.getCenter().y, point.y);
}

BOOST_AUTO_TEST_CASE(composite_shape_move_by_delta_center_correctness)
{
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>
      (pochetnyi::point_t{ 0.0, 0.0 }, pochetnyi::point_t{ 11.0, 47.0 }, pochetnyi::point_t{ -46.0, 82.0 });
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{42.0, 19.0}, 16.0, 35.0);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(triang);
  cShape.addShape(rect);
  const double dx = 5.0;
  const double dy = 12.0;
  const pochetnyi::point_t center = cShape.getCenter();
  cShape.move(dx, dy);
  BOOST_CHECK_CLOSE(cShape.getCenter().x, center.x + dx, delta);
  BOOST_CHECK_CLOSE(cShape.getCenter().y, center.y + dy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_scale)

BOOST_AUTO_TEST_CASE(composite_shape_scale_less_or_equal_zero_coefficient_exception_throw)
{
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ -117.0, 35.61 }, 18.155, 422.019);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  BOOST_CHECK_THROW(cShape.scale(-21.0), std::invalid_argument);
  BOOST_CHECK_THROW(cShape.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(composite_shape_scale_center_frame_rect_correctness)
{
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 17.0, -5.6 }, 22.5);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 19.2, 11.3 }, 6.0, 9.5);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(circ);
  cShape.addShape(rect);
  const pochetnyi::point_t center = cShape.getCenter();
  const pochetnyi::rectangle_t frameRect = cShape.getFrameRect();
  const double coef = 7.0;
  cShape.scale(coef);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, frameRect.width * coef, delta);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, frameRect.height * coef, delta);
  BOOST_CHECK_CLOSE(cShape.getCenter().x, center.x, delta);
  BOOST_CHECK_CLOSE(cShape.getCenter().y, center.y, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_rotate)

BOOST_AUTO_TEST_CASE(composite_shape_rotate_center_frame_rect_correctness)
{
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 11.5, -13.6 },
      pochetnyi::point_t{ 37.8, 19.8 }, pochetnyi::point_t{ 3.5, 14.82 });
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 16.9, 45.6 }, 17.0);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(triang);
  cShape.addShape(circ);
  const double cx = cShape.getCenter().x;
  const double cy = cShape.getCenter().y;
  const double width = cShape.getFrameRect().width;
  const double height = cShape.getFrameRect().height;
  const double degrees = 90.0;
  cShape.rotate(degrees);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, height, delta);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, width, delta);
  BOOST_CHECK_CLOSE(cShape.getCenter().x, cx, delta);
  BOOST_CHECK_CLOSE(cShape.getCenter().y, cy, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_area)

BOOST_AUTO_TEST_CASE(composite_shape_constructor_area_correctness)
{
  const double width = 113.5;
  const double height = 67.1;
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ -11.0, -18.0 }, width, height);
  const double radius = 2.9;
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>
      (pochetnyi::point_t{ 256.6, 219.0 }, radius);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  cShape.addShape(circ);
  BOOST_CHECK_CLOSE(cShape.getArea(), width * height + M_PI * radius * radius, delta);
}

BOOST_AUTO_TEST_CASE(composite_shape_move_to_point_returns_equal_area)
{
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 113.5, 67.1 }, 17.0);
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>
      (pochetnyi::point_t{ 25.61, -11.75 }, pochetnyi::point_t{ 18.3, 61.38 }, pochetnyi::point_t{ 9.99, -1.12 });
  pochetnyi::CompositeShape cShape;
  cShape.addShape(circ);
  cShape.addShape(triang);
  double area = cShape.getArea();
  const pochetnyi::point_t point{ 5.0, 3.0 };
  cShape.move(point);
  BOOST_CHECK_CLOSE(cShape.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(composite_shape_move_by_delta_returns_equal_area)
{
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 12.2, 14.87 }, 14.78, 55.1);
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>
      (pochetnyi::point_t{ 13.16, -19.88 }, pochetnyi::point_t{ 16.503, 61.71 }, pochetnyi::point_t{ 5.0, -1.0 });
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  cShape.addShape(triang);
  double area = cShape.getArea();
  const double dx = 14.0;
  const double dy = 28.0;
  cShape.move(dx, dy);
  BOOST_CHECK_CLOSE(cShape.getArea(), area, delta);
}

BOOST_AUTO_TEST_CASE(composite_shape_scale_area_correctness)
{
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 13.85, 54.03 }, 66.6, 6.66);
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 77.5, 48.15 }, 61.2);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  cShape.addShape(circ);
  double area = cShape.getArea();
  const double coef = 11.1;
  cShape.scale(coef);
  BOOST_CHECK_CLOSE(cShape.getArea(), area * coef * coef, delta);
}

BOOST_AUTO_TEST_CASE(composite_shape_rotate_area_correctness)
{
 pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 18.0, -6.7 }, 34.3);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 92.4, 15.8 }, 8.0, 29.6);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  cShape.addShape(circ);
  double area = cShape.getArea();
  const double degrees = 110.0;
  cShape.rotate(degrees);
  BOOST_CHECK_CLOSE(cShape.getArea(), area, delta);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_add_shape)

BOOST_AUTO_TEST_CASE(composite_shape_add_shape_count_correctness)
{
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 0.0, 0.0 },
      pochetnyi::point_t{ 28.0, 0.0 }, pochetnyi::point_t{ 0.0, 19.0 });
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 17.3, 60.5 }, 10.0);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{8.2, 11.62}, 29.0, 3.5);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(triang);
  cShape.addShape(circ);
  cShape.addShape(rect);
  BOOST_CHECK_EQUAL(cShape.getCount(), 3);
  BOOST_CHECK_EQUAL(cShape[1], circ);
  BOOST_CHECK_EQUAL(cShape[2], rect);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_remove_shape)

BOOST_AUTO_TEST_CASE(composite_shape_remove_shape_index_out_of_range_exception_throw)
{
  pochetnyi::CompositeShape cShape;
  BOOST_CHECK_THROW(cShape.removeShape(0), std::out_of_range);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 116.9, 87.93 }, 27.56, 81.03);
  cShape.addShape(rect);
  BOOST_CHECK_THROW(cShape.removeShape(3), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(composite_shape_remove_shape_count_correctness)
{
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 10.0, -11.0 },
      pochetnyi::point_t{ 73.5, 18.9 }, pochetnyi::point_t{ 6.8, 13.28 });
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 18.7, 41.9 }, 12.0);
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 64.3, 38.2 }, 91.7, 32.4);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(triang);
  cShape.addShape(circ);
  cShape.addShape(rect);
  size_t count = cShape.getCount();
  BOOST_CHECK_NO_THROW(cShape.removeShape(1));
  BOOST_CHECK_EQUAL(cShape.getCount(), count - 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(composite_shape_index)

BOOST_AUTO_TEST_CASE(composite_shape_index_out_of_range_exception_throw)
{
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 55.1, 36.6 }, 61.18, 44.3);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(rect);
  BOOST_CHECK_THROW(cShape[3], std::out_of_range);
  BOOST_CHECK_THROW(cShape[-3], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(composite_shape_index_list_correctess)
{
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 32.09, -11.05 },
      pochetnyi::point_t{ 77.03, 16.29 }, pochetnyi::point_t{ 65.78, 11.17 });
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>
      (pochetnyi::point_t{ 22.3, 38.5 }, 98.7, 19.6);
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 23.84, 46.93 }, 11.5);
  pochetnyi::CompositeShape cShape;
  cShape.addShape(triang);
  cShape.addShape(rect);
  cShape.addShape(circ);
  BOOST_CHECK_NO_THROW(cShape[1]);
  BOOST_CHECK_EQUAL(cShape[1], rect);
  BOOST_CHECK_EQUAL(cShape[2], circ);
}

BOOST_AUTO_TEST_SUITE_END()
