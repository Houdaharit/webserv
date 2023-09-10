#include "Request.hpp"

int main()
{
	std::string request("POST /example HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"key1\": \"value1\", \"key2\": \"value2\"}");
	std::string request2("POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n4\r\n{\"id\":\r\n7\r\n\":1234,\r\n8\r\n\"name\":\r\n6\r\n\"John\"}\r\n0\r\n");
	std::string request3("POST /api/endpoint HTTP/1.1\r\nHost: example.com\r\nUser-Agent: MyHttpClient/1.0\r\nContentType: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHello\r\n7\r\n, world!\r\n0\r\n\r\n");
	HttpRequest httprequest;
	httprequest.parse(request3);
	return 0;
}
