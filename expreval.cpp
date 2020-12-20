#include <iostream>
#include <string>
#include <getopt.h>
#include <expreval.h>

#define DEFAULT_SPECIFICATION_FILE_PATH "operators.spec"

using namespace std;

int main(int argc, char** argv){
    ExprEval::Expression expr;
    string str;

    // ExprEval::Function f({"x", "y"}, "x*y/100");
    // ExprEval::Function g({"x[0]", "x[1]"}, f.get({"x[0]-x[1]", "80-x[1]"}) + "+x[0]*x[1]");

    // try
    // {
    //     cout << f.get({4, 50}) << " = " << f({4, 50}) << endl;
    //     cout << g.get({4, 50}) << " = " << g({4, 50}) << endl;

    //     g.set({"x"}, "3*x+2");
    //     cout << g.get({4}) << " = " << g({4}) << endl;
    // }
    // catch(const ExprEval::Engine::Exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    int c;
    int interactive_flag = 0;

    while (1){
        static struct option long_options[] =
        {
            {"interactive",   no_argument,       &interactive_flag, 1},
            {0, 0, 0, 0}
        };
    
        /* getopt_long stores the option index here. */
        int option_index = 0;
        c = getopt_long(argc, argv, "i:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
            {
            case 0:
            /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'i':
                cout << " = " << expr.evaluate(string(optarg)) << endl;
                // puts ("option -i\n");
                return 0;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                abort ();
            }
        }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }

    if(interactive_flag){
        cout << "(Enter 'h' for help)" << endl;
    }

    while(1){
        cout<<": ";
        getline(cin, str);
        if(str[0] == 'q') break;
        else if(str[0] == '>' && interactive_flag){
            ExprEval::Operator::CustomOperator custom_operator;
            size_t n_arg;

            cout<<"\t> Symbol: ";
            cin>>custom_operator.symbol;
            cout<<"\t> # Args: ";
            cin>>n_arg;
            for(size_t i=1; i<=n_arg; ++i){
                cout<<"\t> Variable ["<<i<<"]: ";
                string arg;
                cin>>arg;
                if(arg.back() != '_'){
                    cout<<" ! [Variable names should end with underscore(_)]\n";
                    i -= 1;
                    continue;
                }
                custom_operator.arg_positions.push_back(i);
                custom_operator.variables.push_back(arg);
            }
            cout<<"\t> Expression: ";
            cin>>custom_operator.expression;

            ExprEval::Operator::add_custom_operator(custom_operator);
            cout<<"= = = = = = = = = = = = = =\n";
            cin.ignore();
            continue;
        } else if(str[0] == '<' && interactive_flag){
            string symbol;
            cout<<" < Symbol: ";
            cin>>symbol;
            ExprEval::Operator::remove_custom_operator(symbol);
            cout<<"= = = = = = = = = = = = = =\n";
            cin.ignore();
            continue;
        } else if(str[0] == '?' && interactive_flag){
            auto custom_table = ExprEval::Operator::get_custom_table();
            for(size_t i=0; i<custom_table->size(); ++i){
                auto custom_operator = custom_table->at(i);
                auto args = custom_operator.variables;

                cout<<"\t- "<<custom_operator.symbol<<"(";
                for(size_t j=0; j<args.size(); ++j){
                    cout<<args[j];
                    if(j < args.size()-1) cout<<", ";
                }
                cout<<") = "<<custom_operator.expression<<endl;
            }
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        } else if(str[0] == 's' && interactive_flag){
            string file_path;

            cout << "\t[w] File path(default: operators.spec): ";
            getline(cin, file_path);
            if(file_path.empty()) file_path = DEFAULT_SPECIFICATION_FILE_PATH;

            try
            {
                ExprEval::Operator::BaseSpecification::write(file_path);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        } else if(str[0] == 'l' && interactive_flag){
            string file_path;

            cout << "\t[r] File path(default: operators.spec): ";
            getline(cin, file_path);
            if(file_path.empty()) file_path = DEFAULT_SPECIFICATION_FILE_PATH;

            try
            {
                ExprEval::Operator::BaseSpecification::read(file_path);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        } else if(str[0] == 'h' && interactive_flag){
            cout << "\t| Use '>' to add a new operator/function;" << endl;
            cout << "\t| Use '<' to remove an operator/function;" << endl;
            cout << "\t| Use '?' to list all the user-defined operators/functions;" << endl;
            cout << "\t| Use 's' to save all the user-defined operators/functions;" << endl;
            cout << "\t| Use 'l' to load all the user-defined operators/functions;" << endl;
            cout << "\t| Use 'q' to quit." << endl;
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        }
        
        try
        {
            cout<<" = "<<expr.evaluate(str)<<endl;
        }
        catch(const ExprEval::Engine::Exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
