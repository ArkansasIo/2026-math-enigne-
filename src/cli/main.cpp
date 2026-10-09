// ---------------------------------------------------------------------------
// MathEngine :: CLI
//
// A tiny interactive front-end to the working API. It demonstrates the two
// implemented entry points and honestly reports the roadmap modules that are
// not yet available, rather than pretending to parse arbitrary expressions.
//
// Usage:
//     mathengine_cli              # interactive REPL
//     mathengine_cli --help
//     mathengine_cli --version
//     mathengine_cli --demo       # run the bundled demonstration
// ---------------------------------------------------------------------------

#include <mathengine/mathengine.hpp>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

namespace
{

    void print_banner()
    {
        std::cout << "MathEngine " << MATHENGINE_VERSION_STRING << " (C++26)\n"
                  << "A symbolic/numerical engine scaffold.\n"
                  << "Type 'help' for commands, 'quit' to exit.\n\n";
    }

    void print_help()
    {
        std::cout << "Commands:\n"
                     "  integrate a b        antiderivative of (a*x + b), symbolic\n"
                     "  definite a b lo hi   definite integral of (a*x + b) on [lo, hi]\n"
                     "  demo                 show the documented examples\n"
                     "  help                 show this help\n"
                     "  quit                 exit\n\n"
                     "Only linear integrands are implemented so far. See docs/ROADMAP.md\n"
                     "for the modules that remain architectural interfaces.\n";
    }

    void run_demo()
    {
        using mathengine::definite_integral_linear;
        using mathengine::integrate_linear;

        const auto symbolic = integrate_linear(3, 1);
        std::cout << "  integrate_linear(3, 1)            = " << symbolic.to_string()
                  << "\n"
                  << "  definite_integral_linear(3,1,0,5) = "
                  << definite_integral_linear(3, 1, 0, 5) << "\n";
    }

    /// Reads a `double`-free integer argument, returning false on bad input.
    bool read_long_long(std::istream &in, long long &out)
    {
        in >> out;
        return !in.fail();
    }

} // namespace

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);

    for (int i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];
        if (arg == "--help" || arg == "-h")
        {
            print_help();
            return EXIT_SUCCESS;
        }
        if (arg == "--version" || arg == "-v")
        {
            std::cout << "MathEngine " << MATHENGINE_VERSION_STRING << '\n';
            return EXIT_SUCCESS;
        }
        if (arg == "--demo")
        {
            run_demo();
            return EXIT_SUCCESS;
        }
        std::cerr << "Unknown option: " << arg << "\n";
        print_help();
        return EXIT_FAILURE;
    }

    print_banner();

    std::string command;
    while (true)
    {
        std::cout << "> " << std::flush;
        if (!(std::cin >> command))
        {
            std::cout << '\n';
            break;
        }

        if (command == "quit" || command == "exit")
        {
            break;
        }
        if (command == "help")
        {
            print_help();
            continue;
        }
        if (command == "demo")
        {
            run_demo();
            continue;
        }
        if (command == "integrate")
        {
            long long a = 0, b = 0;
            if (read_long_long(std::cin, a) && read_long_long(std::cin, b))
            {
                std::cout << "  " << mathengine::integrate_linear(a, b).to_string()
                          << '\n';
            }
            else
            {
                std::cin.clear();
                std::cerr << "Usage: integrate a b\n";
            }
            continue;
        }
        if (command == "definite")
        {
            long long a = 0, b = 0, lo = 0, hi = 0;
            if (read_long_long(std::cin, a) && read_long_long(std::cin, b) &&
                read_long_long(std::cin, lo) && read_long_long(std::cin, hi))
            {
                std::cout << "  " << std::setprecision(15)
                          << mathengine::definite_integral_linear(a, b, lo, hi)
                          << '\n';
            }
            else
            {
                std::cin.clear();
                std::cerr << "Usage: definite a b lo hi\n";
            }
            continue;
        }

        std::cerr << "Unrecognised command: " << command
                  << " (try 'help')\n";
    }

    std::cout << "Goodbye.\n";
    return EXIT_SUCCESS;
}
