#include <configuration.h>

Configuration *CFG = new Configuration();

// CONSTRUCTOR
Configuration::Configuration()
{
    SDL_SetWindowIcon(WINDOW, ICON);
};

// METHOD
void Configuration::resizeWindow(int W, int H)
{
    WIDTH = W; HEIGHT = H;
    SDL_SetWindowSize(WINDOW, W, H);
}

void Configuration::addDevlog(string0D text, int colorCode)
{ 
    DEVLOG += "| \033[" + std::to_string(colorCode) + "m" + text + "\033[0m ";
}

void Configuration::printDevlog()
{
    if (DEVLOG == "" || DEVLOG == PRELOG) return;
    PRELOG = DEVLOG;
    std::cout << DEVLOG << "\n";
}

bool Configuration::isComment(string0D str)
{ 
    return  str == "" ||
            str.back() == '#' ||
            str[0] ==  '#';
}

void Configuration::frameHandler()
{
    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_duration = SDL_GetTicks() - frame_start;
    if (frame_duration < DELAY_TIME)
        SDL_Delay(DELAY_TIME - frame_duration);

    RUNTIME++;
}

//-------Covert each line of file into vector--------
string1D Configuration::convertStrVec(string0D file_dir)
{
    std::ifstream inputFile(file_dir);
    string0D line;

    string1D values;

    while (std::getline(inputFile, line))
        if (line != "" && line.back() != '#' && line[0] != '#')
            values.push_back((line));

    return values;
}

string0D Configuration::convertDigit(int number, int maxNumber)
{
    // Calculate the number of digits in the maximum number
    int numDigits = 1;
    int temp = maxNumber;
    while (temp /= 10) numDigits++;

    // Format the number with leading zeros based on the number of digits
    std::ostringstream oss;
    oss << std::setw(numDigits) << std::setfill('0') << number;
    return oss.str();
}

// ------Vector Resizer------
int2D Configuration::resizeInt2D(int1D vec, int r, int c)
{
    int2D result;
    auto it = vec.begin();
    for (int i = 0; i < r; ++i)
    {
        result.push_back(int1D(it, it + c));
        it += c;
    }

    return result;
}
long2D Configuration::resizeLong2D(long1D vec, int r, int c)
{
    long2D result;
    auto it = vec.begin();
    for (int i = 0; i < r; ++i)
    {
        result.push_back(long1D(it, it + c));
        it += c;
    }

    return result;
}
float2D Configuration::resizeFloat2D(float1D vec, int r, int c)
{
    float2D result;
    auto it = vec.begin();
    for (int i = 0; i < r; ++i)
    {
        result.push_back(float1D(it, it + c));
        it += c;
    }

    return result;
}

// -------Convert String to Vector 1D-------
int1D Configuration::convertStrInt1D(string0D str, char delimiter)
{
    int1D values;
    string0D token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
        values.push_back(std::stoi(token));

    return values;
}
float1D Configuration::convertStrFloat1D(string0D str, char delimiter)
{
    float1D values;
    string0D token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
        values.push_back(std::stof(token));

    return values;
}
long1D Configuration::convertStrLong1D(string0D str, char delimiter)
{
    long1D values;
    string0D token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
        values.push_back(std::stol(token));

    return values;
}

// ---------Convert Vec Float to Int---------
int1D Configuration::convertFloat1DInt(float1D vec)
{
    int1D intVec;

    for (float value : vec)
        intVec.push_back(value);

    return intVec;
}
int2D Configuration::convertFloat2DInt(float2D floatVec)
{
    int2D intVec;

    for (const auto& row : floatVec) {
        int1D intRow;

        for (const auto& element : row) {
            int intElement = static_cast<int>(element);
            intRow.push_back(intElement);
        }

        // Add the converted row to the integer vector
        intVec.push_back(intRow);
    }

    return intVec;
}