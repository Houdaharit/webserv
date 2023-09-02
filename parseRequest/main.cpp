#include "Request.hpp"

int main()
{
	std::string request("POST /example HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"key1\": \"value1\", \"key2\": \"value2\"}");
	std::string request2("POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n4\n{\"id\":\n7\n\":1234,\n8\n\"name\":\n6\n\"John\"}\n0\n");
	HttpRequest httprequest;
	httprequest.parse(request2);
	return 0;
}
