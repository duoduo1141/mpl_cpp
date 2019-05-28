
#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"
#include "robotModel.hpp"
#include "tf_Graph.hpp"


class TF_GraphTest : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        YAML::Node robot_dict = YAML::LoadFile("/home/liujianran/temp/mpl_cpp/mechmind_yaml_model.yaml");
        pRobot = std::make_shared<RobotModel::RobotModel>(robot_dict);
        pTree = std::make_shared<tf_Graph::TF_Graph>(pRobot->mTf_tree);
    }

    std::shared_ptr<RobotModel::RobotModel>  pRobot;
    std::shared_ptr<tf_Graph::TF_Graph> pTree;
};

TEST_F(TF_GraphTest, isLeafFrame)
{
    EXPECT_TRUE(pTree->isLeafFrame("tool0"));
    EXPECT_FALSE(pTree->isLeafFrame("link_1"));
}

TEST_F(TF_GraphTest, rmFrame)
{
    EXPECT_FALSE(pTree->rmFrame("link_1"));
    EXPECT_TRUE(pTree->rmFrame("tool0"));

    bool flag = false;
    for(auto item: pTree->Vmap )
    {
        EXPECT_NE(item.first, "tool0");
        if(item.first == "link_1")
        {
            flag = true;
        }
    }
    EXPECT_TRUE(flag);

}

TEST_F(TF_GraphTest, rmFrame_recursive)
{
    EXPECT_TRUE(pTree->rmFrame_recursive("link_1"));
   
    bool flag = false;
    for(auto item: pTree->Vmap )
    {
        EXPECT_NE(item.first, "link_6");
        EXPECT_NE(item.first, "link_2");
        if(item.first == "base_link")
        {
            flag = true;
        }
    }
    EXPECT_TRUE(flag);
}