#ifndef RETOUCH_OPTIONS_HPP
#define RETOUCH_OPTIONS_HPP

#include "extern/cxxopts/cxxopts.hpp"
#include "colorize.hpp"

#include <iostream>
#include <memory>

std::string basename(std::string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

std::string getCommand(int argc, const char* argv[]) {
    std::string command = "default";
    if (argc>1) {
        command = argv[1];
    }
    return command;
}

bool parseCommandDefault(int argc, const char* argv[])
{
    std::cout << "default" << std::endl;
    return true;
}

bool parseCommandInit(int argc, const char* argv[])
{
    std::string program = basename(argv[0]); 
    argv++; argc--;
    if (argc>0) {
        try
        {
            std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(program+" "+argv[0], Esc::fgBlue +  program+" "+argv[0] +": Example command line options" + Esc::reset ));
            cxxopts::Options& options = *allocated;
            options.positional_help("[optional args]").show_positional_help();
            options
            .set_width(70)
            .set_tab_expansion()
            //.allow_unrecognised_options()
            .add_options()
                ("o,original","Original github repository", cxxopts::value<std::string>(),"<URL>")
                ("m,modified","Modified github repository", cxxopts::value<std::string>(),"<URL>")
                ("h,help","Print help")
            ;
            auto result = options.parse(argc, argv);

            if (result.count("help"))
            {
                std::cout << options.help({"", "Group"}) << std::endl;
                return true;
            }

            //std::cout << "Arguments remain = " << argc << std::endl;
            //auto arguments = result.arguments();
            //std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

            if (result.unmatched().size()) {
                std::cout << std::endl << Esc::bgRed << Esc::bright << Esc::fgYellow << " ERROR!!! " << result.unmatched().size() << " unmatched options: ";
                for (const auto& option: result.unmatched())
                {
                  std::cout << "'" << option << "' ";
                }
                std::cout << Esc::reset << std::endl << std::endl;            
                std::cout << options.help({"", "Group"}) << std::endl;
                return false;
            }
                    
        }
        catch (const cxxopts::exceptions::exception& e)
        {
            std::cout << "error parsing options: " << e.what() << std::endl;
            return false;
        }
    }
    return true;
}

bool parseCommandUnknown(int argc, const char* argv[])
{
    argv++; argc--;
    if (argc>0) std::cout << Esc::bgRed << Esc::fgYellow << Esc::bright << " " << argv[0] << Esc::normalColorOrIntensity << ": unknown command " << Esc::reset << std::endl;
    return false;
}

bool parseCommand(int argc, const char* argv[]) {
    std::string command = getCommand(argc, argv);
    if (command=="default")
    {
        return parseCommandDefault(argc, argv);
    }
    else if (command=="init")
    {
        return parseCommandInit(argc, argv);
    }
    else
    {
        return parseCommandUnknown(argc, argv);
    }
    return true;
}


int parseOptions(int argc, const char* argv[])
{
  try
  {
    std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(argv[0], " - example command line options"));
    auto& options = *allocated;
    options
      .positional_help("[optional args]")
      .show_positional_help();

    bool apple = false;

    options
      .set_width(70)
      .set_tab_expansion()
      .allow_unrecognised_options()
      .add_options()
      ("command","",cxxopts::value<std::string>(),"FILE")
      ;

/*
      .add_options()
      ("a,apple,ringo", "an apple", cxxopts::value<bool>(apple))
      ("b,bob", "Bob")
      ("char", "A character", cxxopts::value<char>())
      ("t,true", "True", cxxopts::value<bool>()->default_value("true"))
      ("f, file", "File", cxxopts::value<std::vector<std::string>>(), "FILE")
      ("i,input", "Input", cxxopts::value<std::string>())
      ("o,output", "Output file", cxxopts::value<std::string>()->default_value("a.out")->implicit_value("b.def"), "BIN")
      ("x", "A short-only option", cxxopts::value<std::string>())
      ("positional","Positional arguments: these are the arguments that are entered without an option", cxxopts::value<std::vector<std::string>>())
      ("long-description", "thisisareallylongwordthattakesupthewholelineandcannotbebrokenataspace")
      ("help", "Print help")
      ("tab-expansion", "Tab\texpansion")
      ("int", "An integer", cxxopts::value<int>(), "N")
      ("float", "A floating point number", cxxopts::value<float>())
      ("vector", "A list of doubles", cxxopts::value<std::vector<double>>())
      ("option_that_is_too_long_for_the_help", "A very long option")
      ("l,list", "List all parsed arguments (including default values)")
      ("range", "Use range-for to list arguments")
    #ifdef CXXOPTS_USE_UNICODE
      ("unicode", u8"A help option with non-ascii: à. Here the size of the string should be correct")
    #endif
    ;
*/
    options.add_options("Group")
      ("c,compile", "compile")
      ("d,drop", "drop", cxxopts::value<std::vector<std::string>>());

//    options.parse_positional({"input", "output", "positional"});
    options.parse_positional({"command"});

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      return true;
    }

    if(result.count("list"))
    {
      if(result.count("range"))
      {
        for(const auto &kv: result)
        {
          std::cout << kv.key() << " = " << kv.value() << std::endl;
        }
      }
      else
      {
        std::cout << result.arguments_string() << std::endl;
      }
      return true;
    }

    if (apple)
    {
      std::cout << "Saw option ‘a’ " << result.count("a") << " times " <<
        std::endl;
    }

    if (result.count("b"))
    {
      std::cout << "Saw option ‘b’" << std::endl;
    }

    if (result.count("char"))
    {
      std::cout << "Saw a character ‘" << result["char"].as<char>() << "’" << std::endl;
    }

    if (result.count("f"))
    {
      auto& ff = result["f"].as<std::vector<std::string>>();
      std::cout << "Files" << std::endl;
      for (const auto& f : ff)
      {
        std::cout << f << std::endl;
      }
    }

    if (result.count("input"))
    {
      std::cout << "Input = " << result["input"].as<std::string>()
        << std::endl;
    }

    if (result.count("output"))
    {
      std::cout << "Output = " << result["output"].as<std::string>()
        << std::endl;
    }

    if (result.count("positional"))
    {
      std::cout << "Positional = {";
      auto& v = result["positional"].as<std::vector<std::string>>();
      for (const auto& s : v) {
        std::cout << s << ", ";
      }
      std::cout << "}" << std::endl;
    }

    if (result.count("int"))
    {
      std::cout << "int = " << result["int"].as<int>() << std::endl;
    }

    if (result.count("float"))
    {
      std::cout << "float = " << result["float"].as<float>() << std::endl;
    }

    if (result.count("vector"))
    {
      std::cout << "vector = ";
      const auto values = result["vector"].as<std::vector<double>>();
      for (const auto& v : values) {
        std::cout << v << ", ";
      }
      std::cout << std::endl;
    }

    std::cout << "Arguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

    std::cout << "Unmatched options: ";
    for (const auto& option: result.unmatched())
    {
      std::cout << "'" << option << "' ";
    }
    std::cout << std::endl;
  }
  catch (const cxxopts::exceptions::exception& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    return false;
  }

  return true;
}

int parse2(int argc, const char* argv[])
{
  try
  {
    std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(argv[0], " - example command line options"));
    auto& options = *allocated;
    options
      .positional_help("[optional args]")
      .show_positional_help();

    bool apple = false;

    options
      .set_width(70)
      .set_tab_expansion()
      .allow_unrecognised_options()
      .add_options()
      ("a,apple,ringo", "an apple", cxxopts::value<bool>(apple))
      ("b,bob", "Bob")
      ("char", "A character", cxxopts::value<char>())
      ("t,true", "True", cxxopts::value<bool>()->default_value("true"))
      ("f, file", "File", cxxopts::value<std::vector<std::string>>(), "FILE")
      ("i,input", "Input", cxxopts::value<std::string>())
      ("o,output", "Output file", cxxopts::value<std::string>()
          ->default_value("a.out")->implicit_value("b.def"), "BIN")
      ("x", "A short-only option", cxxopts::value<std::string>())
      ("positional",
        "Positional arguments: these are the arguments that are entered "
        "without an option", cxxopts::value<std::vector<std::string>>())
      ("long-description",
        "thisisareallylongwordthattakesupthewholelineandcannotbebrokenataspace")
      ("help", "Print help")
      ("tab-expansion", "Tab\texpansion")
      ("int", "An integer", cxxopts::value<int>(), "N")
      ("float", "A floating point number", cxxopts::value<float>())
      ("vector", "A list of doubles", cxxopts::value<std::vector<double>>())
      ("option_that_is_too_long_for_the_help", "A very long option")
      ("l,list", "List all parsed arguments (including default values)")
      ("range", "Use range-for to list arguments")
    #ifdef CXXOPTS_USE_UNICODE
      ("unicode", u8"A help option with non-ascii: à. Here the size of the"
        " string should be correct")
    #endif
    ;

    options.add_options("Group")
      ("c,compile", "compile")
      ("d,drop", "drop", cxxopts::value<std::vector<std::string>>());

    options.parse_positional({"input", "output", "positional"});

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      return true;
    }

    if(result.count("list"))
    {
      if(result.count("range"))
      {
        for(const auto &kv: result)
        {
          std::cout << kv.key() << " = " << kv.value() << std::endl;
        }
      }
      else
      {
        std::cout << result.arguments_string() << std::endl;
      }
      return true;
    }

    if (apple)
    {
      std::cout << "Saw option ‘a’ " << result.count("a") << " times " <<
        std::endl;
    }

    if (result.count("b"))
    {
      std::cout << "Saw option ‘b’" << std::endl;
    }

    if (result.count("char"))
    {
      std::cout << "Saw a character ‘" << result["char"].as<char>() << "’" << std::endl;
    }

    if (result.count("f"))
    {
      auto& ff = result["f"].as<std::vector<std::string>>();
      std::cout << "Files" << std::endl;
      for (const auto& f : ff)
      {
        std::cout << f << std::endl;
      }
    }

    if (result.count("input"))
    {
      std::cout << "Input = " << result["input"].as<std::string>()
        << std::endl;
    }

    if (result.count("output"))
    {
      std::cout << "Output = " << result["output"].as<std::string>()
        << std::endl;
    }

    if (result.count("positional"))
    {
      std::cout << "Positional = {";
      auto& v = result["positional"].as<std::vector<std::string>>();
      for (const auto& s : v) {
        std::cout << s << ", ";
      }
      std::cout << "}" << std::endl;
    }

    if (result.count("int"))
    {
      std::cout << "int = " << result["int"].as<int>() << std::endl;
    }

    if (result.count("float"))
    {
      std::cout << "float = " << result["float"].as<float>() << std::endl;
    }

    if (result.count("vector"))
    {
      std::cout << "vector = ";
      const auto values = result["vector"].as<std::vector<double>>();
      for (const auto& v : values) {
        std::cout << v << ", ";
      }
      std::cout << std::endl;
    }

    std::cout << "Arguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

    std::cout << "Unmatched options: ";
    for (const auto& option: result.unmatched())
    {
      std::cout << "'" << option << "' ";
    }
    std::cout << std::endl;
  }
  catch (const cxxopts::exceptions::exception& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    return false;
  }

  return true;
}

#endif // RETOUCH_OPTIONS_HPP