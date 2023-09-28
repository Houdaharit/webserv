#include "Request.hpp"

int main()
{
	std::string request("POST /example HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: 35\r\n\r\n{\"key1\": \"value1\", \"key2\": \"value2\"}");
	std::string request2("POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n4\r\n{\"id\":\r\n7\r\n\":1234,\r\n8\r\n\"name\":\r\n6\r\n\"John\"}\r\n0\r\n");
	std::string request3("POST /api/endpoint HTTP/1.1\r\nHost: example.com\r\nUser-Agent: MyHttpClient/1.0\r\nContentType: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHello\r\n7\r\n, world!\r\n0\r\n\r\n");

std::string request4("GET /example HTTP/1.1\r\nHost: example.com\r\n");
std::string request5("POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: multipart/form-data; boundary=--------------------------1234567890\r\nContent-Length: 200\r\n\r\n--------------------------1234567890\r\nContent-Disposition: form-data; name=\"text_field\"\r\n\r\nSome additional text fields can be included here.\r\n--------------------------1234567890\r\nContent-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\nContent-Type: text/plain\r\n\r\nThis is the content of the example.txt file.\r\nIt can contain plain text or binary\r\n--------------------------1234567890--\r\n");
	HttpRequest httprequest;
	httprequest.parse(request5);
	return 0;
}
