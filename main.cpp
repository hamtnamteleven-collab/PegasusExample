// Pegasus Example Code

#include <iostream>
#include <string>
#include "pegasus_client.h"

using namespace std;

namespace pegasus {

    class PegasusClient {
    public:
        PegasusClient(const string& cluster_name, const string& app_name)
            : client_(get_client(cluster_name.c_str(), app_name.c_str())) {
            if (!client_) {
                throw runtime_error("Failed to initialize Pegasus client");
            }
        }

        ~PegasusClient() {
            if (client_) {
                pegasus_client_destroy(client_);
            }
        }

        bool send_message(const string& message) {
            return pegasus_client_send(client_, message.c_str(), message.size()) == 0;
        }

    private:
        pegasus_client* client_;
    };

    pegasus_client* get_client(const char* cluster_name, const char* app_name) {
        if (!pegasus::pegasus_client_factory::initialize("config.ini")) {
            fprintf(stderr, "ERROR: init pegasus failed\n");
            return nullptr;
        }
        return pegasus::pegasus_client_factory::get_client(cluster_name, app_name);
    }

} // namespace pegasus

int main() {
    try {
        pegasus::PegasusClient client("my_cluster", "my_app");
        if (client.send_message("Hello, Pegasus!")) {
            cout << "Message sent successfully!" << endl;
        } else {
            cout << "Failed to send message." << endl;
        }
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}
