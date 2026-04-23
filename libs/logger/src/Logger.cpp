#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

#include "Logger.h"

void init_logger() {
    boost::log::add_file_log(boost::log::keywords::file_name = "loggingFile_%Y-%m-%d_%H-%M-%S.log", boost::log::keywords::format = "[%TimeStamp%] %Message%");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    boost::log::add_common_attributes();
}

void write_info(const std::string &log) { BOOST_LOG_TRIVIAL(info) << log; }
