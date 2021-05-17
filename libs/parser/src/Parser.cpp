#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Logger.h"
#include "Parser.h"

std::vector<std::shared_ptr<Stage>> Parser::parseFile(const std::string &filename) {
    init_logger("parsing.log");
    write_info("Start parsing map");

    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filename, tree);

    const auto &mapTree = tree.get_child("map");

    std::vector<std::shared_ptr<Stage>> stages;

    for (const auto &itStagesTree : mapTree) {
        write_info("Parsing stage");

        std::string nameStage;
        boost::property_tree::ptree stageTree;

        std::tie(nameStage, stageTree) = itStagesTree;

        if (nameStage != "stage") {
            continue;
        }

        Stage stage;

        write_info("Parsing elements");
        for (const auto &itElementsTree : stageTree) {

            std::string nameElement;
            boost::property_tree::ptree elementTree;

            std::tie(nameElement, elementTree) = itElementsTree;

            if (nameElement != "element") {
                continue;
            }

            Point start(elementTree.get<float>("<xmlattr>.startX"), elementTree.get<float>("<xmlattr>.startY"));
            Point end(elementTree.get<float>("<xmlattr>.endX"), elementTree.get<float>("<xmlattr>.endY"));
            Point center(elementTree.get<float>("<xmlattr>.centerX"), elementTree.get<float>("<xmlattr>.centerY"));

            auto figure = elementTree.get<std::string>("<xmlattr>.name");

            if (figure == "line") {
                std::shared_ptr<Line> line_pointer(new Line(start, end, center));
                stage.elements.push_back(line_pointer);
            } else if (figure == "arc") {
                std::shared_ptr<Arc> arc_pointer(new Arc(start, end, center));
                stage.elements.push_back(arc_pointer);
            } else if (figure == "propeller") {
                auto isDynamic = elementTree.get<bool>("<xmlattr>.dynamic");
                std::shared_ptr<Propeller> propeller_pointer(new Propeller(start, end, center, isDynamic));
                stage.elements.push_back(propeller_pointer);
            } else if (figure == "accelerator") {
                std::shared_ptr<Accelerator> accelerator_pointer(new Accelerator(start, end, center));
                stage.elements.push_back(accelerator_pointer);
            } else if (figure == "delayer") {
                std::shared_ptr<Delayer> delayer_pointer(new Delayer(start, end, center));
                stage.elements.push_back(delayer_pointer);
            } else if (figure == "portal") {
                std::shared_ptr<Portal> portal_pointer(new Portal(start, end, center));
                stage.elements.push_back(portal_pointer);
            } else if (figure == "finish") {
                std::shared_ptr<Finish> finish_pointer(new Finish(start, end, center));
                stage.elements.push_back(finish_pointer);
            }
        }
        write_info("Filling stage with elements");
        std::shared_ptr<Stage> stagePointer(new Stage(stage));
        stages.push_back(stagePointer);
    }
    write_info("Returning all stages");

    return stages;
}
