#pragma once

#include "Node.h"
#include "Branch.h"

namespace nTiled {
namespace pipeline {
namespace hierarchical {
namespace lo {

class Leaf : public Node {
public:
  Leaf(Parent* p_parent, unsigned char index);
  Leaf(Parent* p_parent, 
       unsigned char index, 
       const std::vector<GLuint>& light_index_list);

  virtual ~Leaf() {}

  virtual void addSLTNode(const SingleLightTree& slt,
                          const slt::Node& node) override;

  virtual void addLight(GLuint light_index) override;

  virtual void addPartialNode(const SingleLightTree& slt,
                              const slt::PartialLightNode& partial_node) override;

  virtual bool isEmpty() const override { return this->light_index_list.empty(); }


  std::vector<GLuint> getLightIndices() const { return std::vector<GLuint>(this->light_index_list); }

  virtual glm::bvec2 toHashNode() const;

  virtual void extractData(glm::uvec3 point,
                           std::vector<std::pair<glm::uvec3, glm::bvec2>>& hash_nodes,
                           std::vector<std::pair<glm::uvec3, glm::uvec2>>& leaf_nodes,
                           std::vector<GLuint>& light_index_list,
                           std::vector<std::pair<glm::uvec3, Node*>> next_nodes) const;

  virtual void getSubNodes(glm::uvec3 current_point, std::vector<std::pair<glm::uvec3, Node*>>& node_list);

  virtual void exportToJson(rapidjson::Writer<rapidjson::StringBuffer>& writer) const override;

protected:
  virtual void addSLTInternal(const SingleLightTree& slt, unsigned int depth, glm::uvec3 current_middle) override;

private:
  Branch* replaceWithBranch();
  std::vector<GLuint> light_index_list;
};

} // lo
}
}
}
