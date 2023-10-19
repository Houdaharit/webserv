#include "response.hpp"
#include <ctime>
#include <cstdlib>


void Response::METHOD_POST()
{
    std::string contentTypeValue;

    boundary = "";

    std::system(("mkdir -p " + std::string(client.getServer().get_location()[X].get_upload())).c_str());

    if (Check_method_config("POST") == 0)
    {
        Build_HTTP_Response(405);
    }

    if (client.getServer().get_location()[X].get_upload().size() == 0)
    {
        Build_HTTP_Response(404);
    }

    client.getRequest().set_uri(client.getServer().get_location()[X].get_upload());

    std::string contentTypeKey = "Content-Type";
    std::map<std::string, std::string>::iterator contentTypeIter = client.getRequest().get_headers().find(contentTypeKey);

    if (contentTypeIter != client.getRequest().get_headers().end()) 
    {
        // Si la clé "Content-Type" est trouvée dans les en-têtes.
        contentTypeValue = contentTypeIter->second;
        //std::cout << "content type value" << contentTypeValue << std::endl;
    }

    size_t boundaryPos = contentTypeValue.find("boundary=");
    //std::cout << "boundaryPos" << boundaryPos << std::endl;

    if (boundaryPos != std::string::npos)
        // Si "boundary=" est trouvé dans la valeur "Content-Type".
        boundary = contentTypeValue.substr(boundaryPos + 9);   // 9 est la longueur de "boundary="
    //std::cout << "boundary :" << boundary << std::endl;

    if (boundary.empty())
    {
        std::string filePath = client.getRequest().get_bodyFileName();
        std::ifstream bodyfile(filePath.c_str());
		std::ostringstream bodycontent;
		bodycontent << bodyfile.rdbuf();
		Body_boundary = bodycontent.str();
		bodyfile.close();
		std::remove(filePath.c_str());
		post_file();
    }

    else 
    {   
        std::ifstream bodyfile;
        bodyfile.open(client.getRequest().get_bodyFileName().c_str());
    	if (!bodyfile)
        {
			Build_HTTP_Response(404); return ;
        }

		std::ostringstream bodycontent;
		bodycontent << bodyfile.rdbuf();
		std::string body = bodycontent.str();


		while(body.size())
        {
			if (body.substr(0, body.find("\r\n")) == "--" + boundary + "--")
				break;

            //std::cout << "madkhalch " << std::endl;
			body = body.erase(0, body.find("\r\n") + 2);
			body = body.erase(0, body.find("\r\n") + 2);
			body = body.erase(0, body.find("\r\n") + 2);
			body = body.erase(0, body.find("\r\n") + 2);
			body = body.erase(0, body.find("\r\n") + 2);

            //std::cout << "body" << std::endl << body << std::endl;

			// PARS BOUDRY HEADER IN MAP //
            std::string line;
            line = body.substr(0, body.find("\r\n"));
	        while(line.find(':') != std::string::npos)
	        {
                std::string key = line.substr(0, line.find(":"));
                std::string value = line.substr(line.find(":") + 1, line.size());
                map_bdry_header[key] = value;
		        body.erase(0, body.find("\r\n") + 2);
		        line = body.substr(0, body.find("\r\n"));
            }
	        body.erase(0, 2);
            /*  ////////////////////////  */

  			Body_boundary = body.substr(0, body.find("--" + boundary) - 2);
			post_file();  
			body.erase(0, body.find("--" + boundary));
		}
    }

    Build_HTTP_Response(201); return ;
}


void Response::post_file()
{
    std::string ext;
    std::string file_upload = client.getRequest().get_uri() + "/";

    if(boundary.empty())
	{
		file_upload += Generate_Random_File_Name();
        std::map<std::string, std::string>::iterator it = client.getRequest().get_headers().find("Content-Type");
        if(it != client.getRequest().get_headers().end())
        {
            std::string content_type = (*it).second;
            std::map<std::string, std::string>::iterator it2;
            for (it2 = extensionToContentType.begin(); it2 != extensionToContentType.end(); ++it2) 
            {
                if (it2->second == content_type) 
                {
                    ext = it2->first;
                    //std::cout << "conteeeeeeeeeent type : ext : " << ext << std::endl;
                    break;
                }
            }   
            file_upload += "." + ext;
        }
    }
    else
    {
        std::map<std::string, std::string>::iterator it1 = map_bdry_header.find("Content-Disposition");
		std::map<std::string, std::string>::iterator it2 = map_bdry_header.find("Content-Type");
		if(it1 != map_bdry_header.end() && it2 != map_bdry_header.end())
		{
			if ((*it1).second.find("filename") != std::string::npos)
			{
				file_upload +=	(*it1).second.erase(0, (*it1).second.find("filename=") + 10);
				file_upload.erase(file_upload.size() - 1, file_upload.size());
			}
			else if (it2 != map_bdry_header.end())
        	{
				file_upload += Generate_Random_File_Name();

                std::string content_type = (*it2).second;
                std::map<std::string, std::string>::iterator it3;
                for (it3 = extensionToContentType.begin(); it3 != extensionToContentType.end(); ++it3) 
                {
                    if (it3->second == content_type) 
                    {
                        ext = it3->first;
                        break;
                    }
                }   
                file_upload += "." + ext;
			}
        }

        else
        {
			file_upload +=  Generate_Random_File_Name();
			std::string content_type = (*it2).second;
            std::map<std::string, std::string>::iterator it4;
            for (it4 = extensionToContentType.begin(); it4 != extensionToContentType.end(); ++it4) 
            {
                if (it4->second == content_type) 
                {
                    ext = it4->first;
                    break;
                }
            }   
            file_upload += "." + ext;
		}
    }
    std::ofstream file(file_upload.c_str());
	file << Body_boundary;
	file.close();
}



std::string  Response::Generate_Random_File_Name() 
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int charsetSize = sizeof(charset) - 1;
    const int fileNameLength = 7;
    std::string randomFileName;

    std::srand(static_cast<unsigned int>(std::time(0))); // Initialisation du générateur de nombres aléatoires

    for (int i = 0; i < fileNameLength; ++i) 
    {
        int randomIndex = std::rand() % charsetSize;
        randomFileName += charset[randomIndex];
    }
    return randomFileName;
}


// POST /upload HTTP/1.1
// Host: example.com
// Content-Type: multipart/form-data; boundary=WebKitFormBoundary7MA4YWxkTrZu0gW

// --WebKitFormBoundary7MA4YWxkTrZu0gW
// Content-Disposition: form-data; name="text_field"

// This is some text data.
// --WebKitFormBoundary7MA4YWxkTrZu0gW
// Content-Disposition: form-data; name="file"; filename="example.jpg"
// Content-Type: image/jpeg

// (Binary data of the image file goes here)
// --WebKitFormBoundary7MA4YWxkTrZu0gW--

