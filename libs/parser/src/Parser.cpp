#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Parser.h"

std::vector<std::shared_ptr<Stage>> Parser::parseFile(const std::string &filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filename, tree);

    const auto &map_tree = tree.get_child("map");

    std::vector<std::shared_ptr<Stage>> stages;

    for (const auto &it_stages_tree : map_tree) {
        std::string name_stage;
        boost::property_tree::ptree stage_tree;

        std::tie(name_stage, stage_tree) = it_stages_tree;

        if (name_stage != "stage") {
            continue;
        }

        Stage stage;
        for (const auto &it_blocks_tree : stage_tree) {
            std::string name_block;
            boost::property_tree::ptree block_tree;

            std::tie(name_block, block_tree) = it_blocks_tree;

            if (name_block != "block") {
                continue;
            }

            Block block;
            for (const auto &it_elements_tree : block_tree) {
                std::string name_element;
                boost::property_tree::ptree element_tree;

                std::tie(name_element, element_tree) = it_elements_tree;

                if (name_element != "element") {
                    continue;
                }

                Point start(element_tree.get<size_t>("<xmlattr>.startX"), element_tree.get<size_t>("<xmlattr>.startY"));
                Point end(element_tree.get<size_t>("<xmlattr>.endX"), element_tree.get<size_t>("<xmlattr>.endY"));
                Point center
                    (element_tree.get<size_t>("<xmlattr>.centerX"), element_tree.get<size_t>("<xmlattr>.centerY"));

                auto figure = element_tree.get<std::string>("<xmlattr>.name");

                if (figure == "line") {
                    std::shared_ptr<Line> line_pointer(new Line(start, end, center, std::make_shared<DrawableLine>(start, end, center)));
                    block.elements.push_back(line_pointer);
                }

                if (figure == "arc") {
                    std::shared_ptr<Arc> arc_pointer(new Arc(start, end, center, std::make_shared<DrawableArc>(start, end, center)));
                    block.elements.push_back(arc_pointer);
                }

//                if (figure == "propeller") {
//                    auto isDynamic = element_tree.get<bool>("<xmlattr>.dynamic");
//                    std::shared_ptr<Propeller> propeller_pointer(new Propeller(start, end, center, isDynamic));
//                    block.elements.push_back(propeller_pointer);
//                }
//
//                if (figure == "accelerator") {
//                    std::shared_ptr<Accelerator> accelerator_pointer(new Accelerator(start, end, center));
//                    block.elements.push_back(accelerator_pointer);
//                }
//
//                if (figure == "delayer") {
//                    std::shared_ptr<Delayer> delayer_pointer(new Delayer(start, end, center));
//                    block.elements.push_back(delayer_pointer);
//                }
//
//                if (figure == "portal") {
//                    std::shared_ptr<Portal> portal_pointer(new Portal(start, end, center));
//                    block.elements.push_back(portal_pointer);
//                }
//
//                if (figure == "finish") {
//                    std::shared_ptr<Finish> finish_pointer(new Finish(start, end, center));
//                    block.elements.push_back(finish_pointer);
//                }
            }

            std::shared_ptr<Block> block_pointer(new Block(block));
            stage.blocks.push_back(block_pointer);
        }
        std::shared_ptr<Stage> stage_pointer(new Stage(stage));
        stages.push_back(stage_pointer);
    }

    return stages;
}
