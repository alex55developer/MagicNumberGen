/*! -----------------------------------------------------------------------
    Есть последовательность идентификаторов, строящаяся по особым правилам:

    1. Первый идентификатор последовательности имеет вид "A1".
       Второй - "A2", третий - "A3" и так далее.
       За "A9" следующий - "B1".
       Следующий после "Z9" имеет вид "A1-A1", потом "A1-A2" и так далее.
       После "A1-Z9" следующим идет "A2-A1".
    2. Максимальная длина идентификатора - ДЕСЯТЬ групп по два символа.
    3. В идентификаторах никогда НЕ ДОЛЖНЫ присутствовать буквы
       "D", "F", "G", "J", "M", "Q", "V", и цифра "0".
    
    функция GetNextSequence получает в качестве входного параметра строку
    с идентификатором из описанной последовательности, и генерирует
    на выходе строку, содержащую следующий идентификатор последовательности.
    
    Например, функция получает "A1-Z9" и возвращает "A2-A1".
    -----------------------------------------------------------------------
    Использована библиотека boost 1.58.0
    Автор: А.Блинов
    март 2013, июль 2015
*/

#include <string>

// --- boost ---
//#define BOOST_LIB_NAME boost_regex
//#include <boost/config/auto_link.hpp>
#include <boost/regex.hpp>
// --- boost ---


using std::string;

class MagicSequence
{
public:
    static bool GetNextSequence(const string& input, string& output);

    static bool ValidateFormat(const string& str)
    {
        // Prohibited symbols are:
        // "D", "F", "G", "J", "M", "Q", "V", and digit "0"
		//     x   xx    x    x     x      x
		// ABC|D|E|FG|HI|J|KL|M|NOP|Q|RSTU|V|WXYZ
        const string substr("[A-C,E,HI,KL,N-P,R-U,W-Z][1-9]");
        const boost::regex expr("^(" + substr + "-){0,9}" + "(" + substr + "){1}$");
        return regex_match(str, expr);
    }

private:
    static char NextChar(const char ch)
    {
        // ABC<D>E<FG>HI<J>KL<M>NOP<Q>RSTU<V>WXYZ
        const static string frst("ABCEHIKLNOPRSTUWXYZ");
        const static string scnd("BCEHIKLNOPRSTUWXYZ?");
        return scnd.at(frst.find_first_of(ch));
    }

    static bool ProcessSeq(const string& input, const string& subs, string& output);
};

bool MagicSequence::ProcessSeq(const string& input, const string& subs, string& output)
{
    // Check input
    const boost::regex expr(subs);
    boost::smatch what;
    if (!boost::regex_match(input, what, expr))
    {
        return false; // wrong input
    }

    const
#ifdef WIN64
        int64_t
#else
        int
#endif
        	pos = int(what.position(1));
    output.assign(input.cbegin(), input.cbegin() + pos);
    string str(what[1]);
    if (str.at(1) != '9')
    {
        output.append(1, str.at(0));
        output.append(1, str.at(1) + 1);
    }
    else
    {
        output.append(1, NextChar(str.at(0)));
        output.append(1, '1');
    }

    const
#ifdef WIN64
        int64_t
#else
        int
#endif
        	nz9 = int(input.length() - pos) / 3 - 1;
    for(int i = 0; i < nz9; ++i)
    {
        output += "-A1";
    }

    return true;
}

bool MagicSequence::GetNextSequence(const string& inputOrig, string& output)
{
    // prepare output
    output.clear();

    if (!ValidateFormat(inputOrig))
    {
        return false; // error: invalid input
    }

    // If last symbol != '9' increment last symbol and return
    if (inputOrig.at(inputOrig.length() - 1) != '9')
    {
        output.assign(inputOrig.cbegin(), inputOrig.cend() - 1);
        output.append(1, inputOrig.at(inputOrig.length() - 1) + 1);
        return ValidateFormat(output);
    }

    // Last symbol == '9': if previous symbol != 'z', increment and return
    const char letter(inputOrig.at(inputOrig.length() - 2));
    if (letter != 'Z')
    {
        output.assign(inputOrig.cbegin(), inputOrig.cend() - 2);
        output.append(1, NextChar(letter));
        output.append(1, '1');
        return ValidateFormat(output);
    }

    // Check and update group
	string input(inputOrig + "-");
	boost::smatch what;

	/*
	const boost::regex expr1("^(?:Z9-){1,9}$");
    if (boost::regex_match(input, what, expr1))
    {
        const
#ifdef WIN64
            int64_t
#else
       	    int
#endif
            nz9 = input.length() / 3;
        _ASSERTE(nz9 > 0);
        output = "A1";
        for(int i = 0; i < nz9; ++i) // ?
        {
            output += "-A1";
            return ValidateFormat(output);
        }
    }
	*/

    const boost::regex expr2("^(?:Z9-){10}$"); // max 10 groups
    if (boost::regex_match(input, what, expr2))
    {
        return false; // that's all, 10 groups MAX
    }

    string expr3("^(?:[A-Z][1-9]-)*(([A-Y][1-9]|Z[1-8])-){1}(?:Z9-)+$");
    if (!ProcessSeq(input, expr3, output))
    {
        return false;
    }

    return ValidateFormat(output);
}
