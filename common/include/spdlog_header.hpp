/*!
 * @author bintjeman
 * @date 25.06.25
 * @name spdlog_header.hpp
 */

#ifndef BNJKIT_SPDLOG_HEADER_HPP
#define BNJKIT_SPDLOG_HEADER_HPP
#pragma once
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif // BNJKIT_SPDLOG_HEADER_HPP
