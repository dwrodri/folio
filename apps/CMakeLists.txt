
add_executable(vectionary VectionaryApp.cpp)

        target_link_libraries(vectionary PRIVATE
                        Cpp20HttpClient::cpp20_http_client nlohmann_json::nlohmann_json)
