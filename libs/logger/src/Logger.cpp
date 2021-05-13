#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

#include "Logger.h"

void init_logger(const std::string &file_name) {
    boost::log::add_file_log(boost::log::keywords::file_name = file_name, boost::log::keywords::format = "[%TimeStamp%] %Message%");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    boost::log::add_common_attributes();
}

void write_info(const std::string &log) { BOOST_LOG_TRIVIAL(info) << log; }