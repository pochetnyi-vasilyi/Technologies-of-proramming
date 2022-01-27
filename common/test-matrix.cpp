#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <cmath>
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

const double delta = 0.0000001;

BOOST_AUTO_TEST_SUITE(matrix_constructor)

BOOST_AUTO_TEST_CASE(matrix_constructor_raws_columns_correctness)
{
  std::unique_ptr<pochetnyi::Matrix> matrix;
  BOOST_CHECK_NO_THROW(matrix = std::make_unique<pochetnyi::Matrix>());
  BOOST_CHECK_EQUAL(matrix->getLayers(), 0);
  BOOST_CHECK_EQUAL(matrix->getLayerSize(), 0);
  matrix->addShape(std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 88.0, 14.0 }, 22.0, 5.0));
  BOOST_CHECK_EQUAL(matrix->getLayers(), 1);
  BOOST_CHECK_EQUAL(matrix->getLayerSize(), 1);
}

BOOST_AUTO_TEST_CASE(matrix_copy_constructor_raws_columns_elements_correctness)
{
  pochetnyi::Matrix matrix;
  matrix.addShape(std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 31.0, 12.0 }, 75.0, 54.0));
  const double raws = matrix.getLayers();
  const double columns = matrix.getLayerSize();
  pochetnyi::Matrix matrix2(matrix);
  BOOST_CHECK_EQUAL(matrix[0][0], matrix2[0][0]);
  BOOST_CHECK_EQUAL(matrix2.getLayers(), raws);
  BOOST_CHECK_EQUAL(matrix2.getLayerSize(), columns);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matrix_operator)

BOOST_AUTO_TEST_CASE(matrix_copy_operator_raws_columns_elements_correctness)
{
  pochetnyi::Matrix matrix;
  matrix.addShape(std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 18.0, 7.0 }, 19.0, 65.0));
  const double raws = matrix.getLayers();
  const double columns = matrix.getLayerSize();
  pochetnyi::Matrix matrix2 = matrix;
  BOOST_CHECK_EQUAL(matrix[0][0], matrix2[0][0]);
  BOOST_CHECK_EQUAL(matrix2.getLayers(), raws);
  BOOST_CHECK_EQUAL(matrix2.getLayerSize(), columns);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matrix_add_shape)

BOOST_AUTO_TEST_CASE(matrix_add_shape_layers_correctness)
{
  pochetnyi::Matrix matrix;
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 19.15, 16.85 }, 2.8, 3.6);
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ -25.3, -47.55 }, 1.9);
  pochetnyi::Shape::SharedShapePtr triang = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 20.0, 17.0 },
      pochetnyi::point_t{ 30.0, 40.0 }, pochetnyi::point_t{ 10.0, 19.0 });
  matrix.addShape(rect);
  matrix.addShape(circ);
  matrix.addShape(triang);
  BOOST_CHECK_EQUAL(matrix.getLayers(), 2);
  BOOST_CHECK_EQUAL(matrix[0][0], rect);
  BOOST_CHECK_EQUAL(matrix[0][1], circ);
  BOOST_CHECK_EQUAL(matrix[1][0], triang);
  BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matrix_index)

BOOST_AUTO_TEST_CASE(matrix_index_out_of_range_exception_throw)
{
  pochetnyi::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
  matrix.addShape(std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ -8.0, 30.0 }, 22.0, 5.5));
  matrix.addShape(std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 4.2, -7.0 }, 3.0));
  BOOST_CHECK_THROW(matrix[10], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(matrix_index_list_correctess)
{
  pochetnyi::Matrix matrix;
  pochetnyi::Shape::SharedShapePtr rect = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 22.3, 38.5 }, 1.7, 2.6);
  pochetnyi::Shape::SharedShapePtr circ = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ -23.84, -46.93 }, 1.5);
  matrix.addShape(rect);
  matrix.addShape(circ);
  BOOST_CHECK_NO_THROW(matrix[0]);
  BOOST_CHECK_EQUAL(matrix[0][0], rect);
  BOOST_CHECK_EQUAL(matrix[0][1], circ);
}

BOOST_AUTO_TEST_SUITE_END()

