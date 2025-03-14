std::vector<std::string> explode(std::string str, char delim = ' ') {
    std::vector<std::string> result;
    std::stringstream stream(str);
    std::string buffer = "";
    while (std::getline(stream, buffer, delim)) {
        result.push_back(buffer);
    }
    return result;
}