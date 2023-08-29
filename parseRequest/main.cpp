#include "Request.hpp"

int main()
{
	std::string request("POST /example HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"key1\": \"value1\", \"key2\": \"value2\"}");
	HttpRequest httprequest;
	httprequest.parse(request);
	return 0;
}
