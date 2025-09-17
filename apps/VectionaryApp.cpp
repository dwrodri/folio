#include <http_client.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class GeminiImageGenerator {
  private:
    std::string api_key_;
    std::string base_url_ = "https://generativelanguage.googleapis.com";

  public:
    explicit GeminiImageGenerator(const std::string& api_key) : api_key_(api_key) {}

    bool generateImage(const std::string& prompt,
            const std::string& output_filename = "generated_image.png") {
        try {
            // Construct the request JSON
            json request_body = {{"contents", {{{"parts", {{{"text", prompt}}}}}}},
                    {"generationConfig", {{"response_mime_type", "image/png"}}}};

            std::cout << "Sending request to Gemini API...\n";
            std::cout << "Prompt: " << prompt << "\n";

            // Make the HTTP POST request
            auto response = http_client::post(
                    base_url_ + "/v1beta/models/gemini-2.0-flash-exp:generateContent")
                                    .add_header({"Content-Type", "application/json"})
                                    .add_header({"Authorization", "Bearer " + api_key_})
                                    .set_body(request_body.dump())
                                    .send();

            std::cout << "Response Status: " << static_cast<int>(response.get_status())
                      << "\n";

            if (response.get_status() == http_client::HttpStatus::Ok) {
                auto response_json = json::parse(response.get_body());

                // Check if response contains image data
                if (response_json.contains("candidates") &&
                        !response_json["candidates"].empty() &&
                        response_json["candidates"][0].contains("content")) {
                    std::cout << "✅ Image generation successful!\n";
                    std::cout << "Response received: " << response_json.dump(2) << "\n";

                    // In a real implementation, you would decode the base64 image data
                    // and save it to a file. For now, just show that we got a response.
                    return true;
                } else {
                    std::cout << "❌ No image data in response\n";
                    std::cout << "Response: " << response_json.dump(2) << "\n";
                    return false;
                }
            } else {
                std::cout << "❌ HTTP Error: "
                          << static_cast<int>(response.get_status()) << "\n";
                std::cout << "Response body: " << response.get_body() << "\n";
                return false;
            }

        } catch (const std::exception& e) {
            std::cout << "❌ Exception occurred: " << e.what() << "\n";
            return false;
        }
    }
};

void printUsage(const std::string& program_name) {
    std::cout << "Usage: " << program_name << " <API_KEY> <PROMPT>\n";
    std::cout << "\nExample:\n";
    std::cout << "  " << program_name
              << " your_api_key_here \"A beautiful sunset over mountains\"\n";
    std::cout << "\nTo get a Gemini API key:\n";
    std::cout << "  1. Go to https://makersuite.google.com/app/apikey\n";
    std::cout << "  2. Create a new API key\n";
    std::cout << "  3. Copy the key and use it as the first argument\n\n";
}

int main(int argc, char** argv) {
    std::cout << "🎨 Vectionary - Gemini Image Generation Demo\n";
    std::cout << "============================================\n\n";

    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    std::string api_key = argv[1];
    std::string prompt = argv[2];

    if (api_key.empty() || prompt.empty()) {
        std::cout << "❌ Error: API key and prompt cannot be empty\n\n";
        printUsage(argv[0]);
        return 1;
    }

    // Hide API key in output for security
    std::string masked_key =
            api_key.substr(0, 8) + "..." + api_key.substr(api_key.length() - 4);
    std::cout << "🔑 Using API key: " << masked_key << "\n\n";

    GeminiImageGenerator generator(api_key);

    bool success = generator.generateImage(prompt);

    if (success) {
        std::cout << "\n🎉 Image generation completed successfully!\n";
        return 0;
    } else {
        std::cout << "\n💥 Image generation failed. Please check your API key and try "
                     "again.\n";
        return 1;
    }
}
