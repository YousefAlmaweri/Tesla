#include <iostream>
#include <string>
#include <vector>   // Used for sorting
#include <algorithm> // Used for std::swap

// Structure to store a configured Tesla's details
struct Car {
    std::string modelDescription; // e.g., "Model Y - Long Range - Ultra Red (FSD)"
    double price;
    Car* next; // Pointer to the next configuration in the linked list
};

// Class to manage saved Tesla configurations using a linked list
class TeslaConfigurator {
private:
    Car* head; // Pointer to the first configuration

public:
    TeslaConfigurator() : head(nullptr) {}

    // Destructor to free all allocated memory for the linked list
    ~TeslaConfigurator() {
        Car* current = head;
        while (current != nullptr) {
            Car* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // Interactive function to configure a new Tesla
    void configureTesla() {
        Car* newConfig = new Car();
        newConfig->price = 0;
        int choice;

        std::cout << "\n--- Step 1: Choose Your Model ---\n";
        std::cout << "1. Model 3 - Long Range ($47,740)\n";
        std::cout << "2. Model Y - Long Range ($50,490)\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            newConfig->modelDescription = "Model 3 - LR";
            newConfig->price += 47740;
        } else {
            newConfig->modelDescription = "Model Y - LR";
            newConfig->price += 50490;
        }

        std::cout << "\n--- Step 2: Choose Your Paint ---\n";
        std::cout << "1. Stealth Grey (Included)\n";
        std::cout << "2. Ultra Red (+$2,000)\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == 2) {
            newConfig->modelDescription += " - Ultra Red";
            newConfig->price += 2000;
        }

        std::cout << "\n--- Step 3: Choose Your Wheels ---\n";
        std::cout << "1. 18\" Photon Wheels (Included)\n";
        std::cout << "2. 19\" Nova Wheels (+$1,500)\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == 2) {
            newConfig->modelDescription += " - 19\" Nova";
            newConfig->price += 1500;
        }

        std::cout << "\n--- Step 4: Add Full Self-Driving ---\n";
        std::cout << "1. No\n";
        std::cout << "2. Yes, add Full Self-Driving Capability (+$8,000)\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == 2) {
            newConfig->modelDescription += " (FSD)";
            newConfig->price += 8000;
        }

        // Display summary and save the configuration
        std::cout << "\n######################################\n";
        std::cout << "### Configuration Saved!           ###\n";
        std::cout << "######################################\n";
        std::cout << "Summary: " << newConfig->modelDescription << "\n";
        std::cout << "Final Price: $" << newConfig->price << "\n";
        
        // Add to the front of the linked list
        newConfig->next = head;
        head = newConfig;
    }

    // Display all saved configurations, sorted by price
    void viewConfigurations() {
        if (head == nullptr) {
            std::cout << "\n###################################\n";
            std::cout << "# No saved configurations found.  #\n";
            std::cout << "###################################\n";
            return;
        }

        // Convert linked list to a vector of pointers for easy sorting
        std::vector<Car*> configs;
        Car* temp = head;
        while (temp != nullptr) {
            configs.push_back(temp);
            temp = temp->next;
        }

        // Sort the vector by price using a simple bubble sort
        for (size_t i = 0; i < configs.size() - 1; i++) {
            for (size_t j = 0; j < configs.size() - i - 1; j++) {
                if (configs[j]->price > configs[j + 1]->price) {
                    std::swap(configs[j], configs[j + 1]);
                }
            }
        }
        
        std::cout << "\n--- Your Saved Configurations (Sorted by Price) ---\n";
        for (const auto& config : configs) {
            std::cout << "---------------------------------\n";
            std::cout << "Configuration: " << config->modelDescription << "\n";
            std::cout << "Price: $" << config->price << "\n";
        }
        std::cout << "---------------------------------\n";
    }

    // Delete a saved configuration by its full description
    void deleteConfiguration() {
        if (head == nullptr) {
            std::cout << "\n# No configurations to delete. #\n";
            return;
        }
        
        std::string modelDesc;
        std::cout << "\nEnter the full description of the configuration to delete: ";
        std::cin.ignore(); 
        std::getline(std::cin, modelDesc);

        Car* prev = nullptr;
        Car* curr = head;

        while (curr != nullptr) {
            if (curr->modelDescription == modelDesc) {
                if (prev != nullptr) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr;
                std::cout << "\n#################################\n";
                std::cout << "## Configuration deleted!      ##\n";
                std::cout << "#################################\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        std::cout << "\n##################################\n";
        std::cout << "##      Config not found!       ##\n";
        std::cout << "##################################\n";
    }
};

int main() {
    TeslaConfigurator savedConfigs;
    int choice;

    do {
        std::cout << "\n**";
        std::cout << "\n* Tesla Vehicle Configurator   *\n";
        std::cout << "\n";
        std::cout << "1. Configure a New Tesla\n";
        std::cout << "2. View Saved Configurations\n";
        std::cout << "3. Delete a Saved Configuration\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                savedConfigs.configureTesla();
                break;
            case 2:
                savedConfigs.viewConfigurations();
                break;
            case 3:
                savedConfigs.deleteConfiguration();
                break;
            case 4:
                std::cout << "\n#################################\n";
                std::cout << "##     Exiting Configurator...   ##\n";
                std::cout << "#################################\n";
                break;
            default:
                std::cout << "\n#################################\n";
                std::cout << "##       Invalid choice!         ##\n";
                std::cout << "#################################\n";
                // Clear input buffer in case of non-integer input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
        }
    } while (choice != 4);

return 0;
}