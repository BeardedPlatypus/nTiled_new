#include <catch.hpp>
#include "pipeline\light-management\hashed\linkless-octree\SpatialHashFunctionBuilder.h"

// ----------------------------------------------------------------------------
//  nTiled Headers
// ----------------------------------------------------------------------------
#include "pipeline\light-management\hashed\linkless-octree\Exceptions.h"

// ----------------------------------------------------------------------------
//  isValidCandidate Scenarios
// ----------------------------------------------------------------------------
/*
 * bool isValidCandidate(glm::u8vec3 candidate,
 *                       unsigned int m_dim,
 *                       const std::vector<glm::uvec3>& elements,
 *                       const std::vector<bool>& hash_defined_table);
 */
SCENARIO("isValidCandidate should throw a SpatialHashFunctionConstructionInvalidArgException if an invalid argument is provided",
         "[LinklessOctreeFull][SpatialHashFunctionFull][SpatialHashFunctionBuilder]") {
  GIVEN("A SpatialHashFunctionBuilder") {
    nTiled::pipeline::hashed::SpatialHashFunctionBuilder<glm::u8vec2> builder =
      nTiled::pipeline::hashed::SpatialHashFunctionBuilder<glm::u8vec2>();

    WHEN("m_dim is zero") {
      glm::u8vec3 cand_1 = glm::u8vec3(0, 0, 0);
      glm::u8vec3 cand_2 = glm::u8vec3(1, 0, 3);
      glm::u8vec3 cand_3 = glm::u8vec3(6, 5, 2);

      std::vector<glm::uvec3> elements_1 = { glm::uvec3(2, 0, 0)};

      std::vector<glm::uvec3> elements_2 = { glm::uvec3(1, 0, 0),
                                             glm::uvec3(0, 1, 0) };

      std::vector<glm::uvec3> elements_3 = { glm::uvec3(1, 0, 0),
                                             glm::uvec3(0, 1, 0),
                                             glm::uvec3(0, 0, 1) };

      std::vector<bool> hash_table_def_empty = { false, false, false, false,
                                                 false, false, false, false,
                                                 false, false, false, false,
                                                 false, false, false, false };

      std::vector<bool> hash_table_def_1 = { false, false, false, false,
                                             true, false, false, false,
                                             false, false, true, false,
                                             false, true, false, false };

      std::vector<bool> hash_table_def_2 = { false, false, false, false,
                                             false, true, true, true,
                                             false, false, false, false,
                                             false, false, false, true };

      std::vector<bool> hash_table_def_3 = { true, true, true, true,
                                             false, false, false, false,
                                             false, false, false, false,
                                             false, false, false, false };

      THEN("A SpatialHashFunctionConstructionInvalidArgException is thrown") {
        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                0,
                                                elements_1, 
                                                hash_table_def_empty),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                0,
                                                elements_1, 
                                                hash_table_def_1),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_2,
                                                0,
                                                elements_2, 
                                                hash_table_def_2),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_3,
                                                0,
                                                elements_3, 
                                                hash_table_def_3),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);
      }
    }

    WHEN("Element size exceeds hash table H size") {
      glm::u8vec3 cand_1 = glm::u8vec3(0, 0, 0);

      std::vector<glm::uvec3> elements_1 = { glm::uvec3(1, 0, 0),
                                             glm::uvec3(0, 1, 0),
                                             glm::uvec3(0, 0, 1),
                                             glm::uvec3(0, 0, 2),
                                             glm::uvec3(0, 0, 5) };

      std::vector<bool> hash_table_def_1 = { false, false, false, false };

      std::vector<bool> hash_table_def_2 = { false, false, false, false,
                                             true, false, false, false,
                                             false, false, true, false,
                                             false, true, false, false };

      std::vector<glm::uvec3> elements_2 = { glm::uvec3(1, 0, 0),
                                             glm::uvec3(0, 1, 0),
                                             glm::uvec3(0, 2, 0),
                                             glm::uvec3(2, 1, 0),
                                             glm::uvec3(0, 1, 0),
                                             glm::uvec3(5, 1, 0),
                                             glm::uvec3(0, 1, 5),
                                             glm::uvec3(0, 1, 2),
                                             glm::uvec3(0, 1, 3),
                                             glm::uvec3(3, 1, 4),
                                             glm::uvec3(2, 1, 2),
                                             glm::uvec3(0, 1, 6),
                                             glm::uvec3(6, 1, 0),
                                             glm::uvec3(5, 2, 0),
                                             glm::uvec3(2, 9, 1),
                                             glm::uvec3(0, 0, 0),
                                             glm::uvec3(3, 3, 1) };

      THEN("A SpatialHashFunctionConstructionInvalidArgException is thrown") {
        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                   2,
                                                   elements_1, 
                                                   hash_table_def_1),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                   4,
                                                   elements_2, 
                                                   hash_table_def_2),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);
      }
    }

    WHEN("Elements is empty") {
      glm::u8vec3 cand_1 = glm::u8vec3(0, 0, 0);
      glm::u8vec3 cand_2 = glm::u8vec3(1, 0, 3);
      glm::u8vec3 cand_3 = glm::u8vec3(6, 5, 2);

      std::vector<glm::uvec3> elements_empty = std::vector<glm::uvec3>();

      std::vector<bool> hash_table_def_empty = { false, false, false, false,
                                                 false, false, false, false,
                                                 false, false, false, false,
                                                 false, false, false, false };

      std::vector<bool> hash_table_def_1 = { false, false, false, false,
                                             true, false, false, false,
                                             false, false, true, false,
                                             false, true, false, false };

      std::vector<bool> hash_table_def_2 = { false, false, false, false,
                                             false, true, true, true,
                                             false, false, false, false,
                                             false, false, false, true };

      std::vector<bool> hash_table_def_3 = { true, true, true, true,
                                             false, false, false, false,
                                             false, false, false, false,
                                             false, false, false, false };

      THEN("A SpatialHashFunctionConstructionInvalidArgException is thrown") {
        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                2,
                                                elements_empty, 
                                                hash_table_def_1),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_2,
                                                2,
                                                elements_empty, 
                                                hash_table_def_2),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_3,
                                                2,
                                                elements_empty, 
                                                hash_table_def_3),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);

        REQUIRE_THROWS_AS(builder.isValidCandidate(cand_1,
                                                2,
                                                elements_empty, 
                                                hash_table_def_empty),
                          nTiled::pipeline::hashed::SpatialHashFunctionConstructionInvalidArgException);
      }
    }
  }
}

SCENARIO("isValidCandidate should return True if the candidate does not cause any conflicts, False otherwise",
         "[LinklessOctreeFull][SpatialHashFunctionFull][SpatialHashFunctionBuilder]") {
  GIVEN("A SpatialHashFunctionBuilder and a set of hash_table_def") {
    nTiled::pipeline::hashed::SpatialHashFunctionBuilder<glm::u8vec2> builder =
      nTiled::pipeline::hashed::SpatialHashFunctionBuilder<glm::u8vec2>();

    std::vector<bool> hash_table_def_empty = { false, false, false,
                                               false, false, false, 
                                               false, false, false,

                                               false, false, false,
                                               false, false, false,
                                               false, false, false,

                                               false, false, false,
                                               false, false, false,
                                               false, false, false };

    std::vector<bool> hash_table_def_0 = { false, false, false,
                                           false, false, false, 
                                           true,  true , false,

                                           false, false, false,
                                           false, false, false,
                                           false, true , false,

                                           false, false, false,
                                           false, false, false,
                                           false, false, false };

    std::vector<bool> hash_table_def_1 = { false, false, true ,
                                           false, false, false, 
                                           false, false, false,

                                           false, false, false,
                                           false, false, false,
                                           false, false, true ,

                                           false, false, false,
                                           false, false, true ,
                                           false, false, false };

    std::vector<bool> hash_table_def_2 = { true , true , true ,
                                           true , true , true ,
                                           true , true , true ,

                                           false, false, false,
                                           false, false, false,
                                           false, false, false,

                                           false, false, false,
                                           false, false, false,
                                           false, false, false };

    WHEN("A list of elements consisting of a single element is provided that does not collide") {
      glm::u8vec3 cand_1 = glm::u8vec3(0, 1, 1);
      glm::u8vec3 cand_2 = glm::u8vec3(0, 2, 1);
      glm::u8vec3 cand_3 = glm::u8vec3(2, 2, 2);

      std::vector<glm::uvec3> elements_single = std::vector<glm::uvec3>();
      elements_single.push_back(glm::uvec3(0, 0, 0));

      THEN("The candidate is valid and the method should return True") {
        REQUIRE(builder.isValidCandidate(cand_1,
                                         3,
                                         elements_single,
                                         hash_table_def_empty));
        REQUIRE(builder.isValidCandidate(cand_2,
                                         3,
                                         elements_single,
                                         hash_table_def_empty));
        REQUIRE(builder.isValidCandidate(cand_3,
                                         3,
                                         elements_single,
                                         hash_table_def_empty));

        REQUIRE(builder.isValidCandidate(cand_1,
                                         3,
                                         elements_single,
                                         hash_table_def_0));
        REQUIRE(builder.isValidCandidate(cand_2,
                                         3,
                                         elements_single,
                                         hash_table_def_0));
        REQUIRE(builder.isValidCandidate(cand_3,
                                         3,
                                         elements_single,
                                         hash_table_def_0));

        REQUIRE(builder.isValidCandidate(cand_1,
                                         3,
                                         elements_single,
                                         hash_table_def_1));
        REQUIRE(builder.isValidCandidate(cand_2,
                                         3,
                                         elements_single,
                                         hash_table_def_1));
        REQUIRE(builder.isValidCandidate(cand_3,
                                         3,
                                         elements_single,
                                         hash_table_def_1));

        REQUIRE(builder.isValidCandidate(cand_1,
                                         3,
                                         elements_single,
                                         hash_table_def_2));
        REQUIRE(builder.isValidCandidate(cand_2,
                                         3,
                                         elements_single,
                                         hash_table_def_2));
        REQUIRE(builder.isValidCandidate(cand_3,
                                         3,
                                         elements_single,
                                         hash_table_def_2));
      }
    }

    WHEN("Candidate is valid for a list of elements consisting of multiple elements") {
      glm::u8vec3 cand = glm::u8vec3(2, 1, 0);

      std::vector<glm::uvec3> elements_two = std::vector<glm::uvec3>();
      elements_two.push_back(glm::uvec3(1, 1, 2));
      elements_two.push_back(glm::uvec3(2, 1, 2));

      std::vector<glm::uvec3> elements_three = std::vector<glm::uvec3>();
      elements_three.push_back(glm::uvec3(1, 1, 2));
      elements_three.push_back(glm::uvec3(2, 1, 2));
      elements_three.push_back(glm::uvec3(1, 0, 2));

      std::vector<glm::uvec3> elements_six= std::vector<glm::uvec3>();
      elements_six.push_back(glm::uvec3(1, 1, 2));
      elements_six.push_back(glm::uvec3(2, 1, 2));
      elements_six.push_back(glm::uvec3(1, 0, 2));
      elements_six.push_back(glm::uvec3(2, 0, 2));
      elements_six.push_back(glm::uvec3(1, 0, 1));
      elements_six.push_back(glm::uvec3(1, 1, 1));

      THEN("A the method should return True") {
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_two,
                                         hash_table_def_0));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_three,
                                         hash_table_def_0));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_six,
                                         hash_table_def_0));

        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_two,
                                         hash_table_def_1));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_three,
                                         hash_table_def_1));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_six,
                                         hash_table_def_1));

        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_two,
                                         hash_table_def_2));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_three,
                                         hash_table_def_2));
        REQUIRE(builder.isValidCandidate(cand,
                                         3,
                                         elements_six,
                                         hash_table_def_2));
      }
    }

    WHEN("Candidate is invalid for a single element in a list of elements consisting of a single element") {
      glm::u8vec3 cand_1 = glm::u8vec3(0, 2, 0);
      glm::u8vec3 cand_2 = glm::u8vec3(2, 2, 1);
      glm::u8vec3 cand_3 = glm::u8vec3(1, 2, 0);

      std::vector<glm::uvec3> elements_single = std::vector<glm::uvec3>();
      elements_single.push_back(glm::uvec3(0, 0, 0));

      THEN("A the method should return False") {
        REQUIRE(builder.isValidCandidate(cand_1,
                                         3,
                                         elements_single,
                                         hash_table_def_0));
        REQUIRE(builder.isValidCandidate(cand_2,
                                         3,
                                         elements_single,
                                         hash_table_def_1));
        REQUIRE(builder.isValidCandidate(cand_3,
                                         3,
                                         elements_single,
                                         hash_table_def_2));
      }
    }

    WHEN("Candidate is invalid for a single element in a list of elements consisting of multiple elements") {
      glm::u8vec3 cand = glm::u8vec3(2, 1, 0);

      std::vector<glm::uvec3> elements_two = std::vector<glm::uvec3>();
      elements_two.push_back(glm::uvec3(1, 1, 0));
      elements_two.push_back(glm::uvec3(2, 1, 2));

      std::vector<glm::uvec3> elements_three = std::vector<glm::uvec3>();
      elements_three.push_back(glm::uvec3(1, 1, 0));
      elements_three.push_back(glm::uvec3(2, 1, 2));
      elements_three.push_back(glm::uvec3(1, 0, 2));

      std::vector<glm::uvec3> elements_six= std::vector<glm::uvec3>();
      elements_six.push_back(glm::uvec3(1, 1, 0));
      elements_six.push_back(glm::uvec3(2, 1, 2));
      elements_six.push_back(glm::uvec3(1, 0, 2));
      elements_six.push_back(glm::uvec3(2, 0, 2));
      elements_six.push_back(glm::uvec3(1, 0, 1));
      elements_six.push_back(glm::uvec3(1, 1, 1));

      THEN("A the method should return False") {
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_two,
                                               hash_table_def_2));
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_three,                                         
                                               hash_table_def_2));
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_six,
                                               hash_table_def_2));
      }
    }

    WHEN("Candidate is invalid for multiple elements in a list of elements consisting of multiple elements") {
      glm::u8vec3 cand = glm::u8vec3(2, 1, 0);

      std::vector<glm::uvec3> elements_two = std::vector<glm::uvec3>();
      elements_two.push_back(glm::uvec3(1, 1, 0));
      elements_two.push_back(glm::uvec3(2, 1, 0));

      std::vector<glm::uvec3> elements_three = std::vector<glm::uvec3>();
      elements_three.push_back(glm::uvec3(1, 1, 0));
      elements_three.push_back(glm::uvec3(2, 1, 0));
      elements_three.push_back(glm::uvec3(1, 0, 2));

      std::vector<glm::uvec3> elements_six= std::vector<glm::uvec3>();
      elements_six.push_back(glm::uvec3(1, 1, 0));
      elements_six.push_back(glm::uvec3(2, 1, 0));
      elements_six.push_back(glm::uvec3(1, 0, 2));
      elements_six.push_back(glm::uvec3(2, 0, 2));
      elements_six.push_back(glm::uvec3(1, 0, 1));
      elements_six.push_back(glm::uvec3(1, 1, 1));


      THEN("A the method should return False") {
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_two,
                                               hash_table_def_2));
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_three,                                         
                                               hash_table_def_2));
        REQUIRE_FALSE(builder.isValidCandidate(cand,
                                               3,
                                               elements_six,
                                               hash_table_def_2));
      }
    }
  }
}