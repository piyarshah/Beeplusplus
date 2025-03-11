#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

class App {
private:
    struct SpeciesInfo {
        std::string description;
        std::vector<std::string> sightings;
        std::vector<std::string> imageUrls;
        int numObservations;
    };

    struct CreatureInfo {
        std::string description;
        std::map<std::string, SpeciesInfo> species;
        int numObservations;
    };

    std::map<std::string, CreatureInfo> creatures;
    int totalObservations;

public:
    App() : totalObservations(0) {}

    void addSighting(const std::string& username, const std::string& creatureType, const std::string& species, const std::string& text) {
        creatures[creatureType].species[species].sightings.push_back("[" + username + "] " + text);
        creatures[creatureType].species[species].numObservations++;
        creatures[creatureType].numObservations++;
        totalObservations++;

        // Prompt the user to add images
        std::cout << "Do you want to add images to this sighting? (y/n): ";
        char addImagesChoice;
        std::cin >> addImagesChoice;

        if (addImagesChoice == 'y' || addImagesChoice == 'Y') {
            std::cout << "Enter the image URLs (separated by spaces): ";
            std::cin.ignore();  // Clear the input buffer
            std::string imageUrl;
            std::getline(std::cin, imageUrl);
            // Split the input into individual image URLs
            std::istringstream iss(imageUrl);
            while (iss >> imageUrl) {
                creatures[creatureType].species[species].imageUrls.push_back(imageUrl);
            }
        }

        std::cout << "Sighting added for " << creatureType << " - " << species << ": " << text << std::endl;
    }

    void viewSightings() {
        if (creatures.empty()) {
            std::cout << "No creature types available." << std::endl;
        } else {
            std::cout << "Total Observations: " << totalObservations << std::endl;
            for (const auto& creature : creatures) {
                std::cout << "Type of creature: " << creature.first;
                if (!creature.second.description.empty()) {
                    std::cout << " - " << creature.second.description;
                }
                std::cout << std::endl;

                if (!creature.second.species.empty()) {
                    for (const auto& species : creature.second.species) {
                        std::cout << "  Species: " << species.first;
                        if (!species.second.description.empty()) {
                            std::cout << " - " << species.second.description;
                        }
                        std::cout << " (Observations: " << species.second.numObservations << ")" << std::endl;

                        if (!species.second.imageUrls.empty()) {
                            std::cout << "  Images:" << std::endl;
                            for (const auto& imageUrl : species.second.imageUrls) {
                                std::cout << "    - " << imageUrl << std::endl;
                            }
                        } else {
                            std::cout << "  No images for this species." << std::endl;
                        }

                        if (!species.second.sightings.empty()) {
                            std::cout << "  Sightings:" << std::endl;
                            for (const auto& sighting : species.second.sightings) {
                                std::cout << "    - " << sighting << std::endl;
                            }
                        } else {
                            std::cout << "  No sightings for this species." << std::endl;
                        }
                    }
                } else {
                    std::cout << "No species for this creature type." << std::endl;
                }

                std::cout << "Total Observations for " << creature.first << ": " << creature.second.numObservations << std::endl;
            }
        }
    }

void addCreatureType(const std::string& creatureType, const std::string& description) {
    creatures[creatureType].description = description;
    creatures[creatureType].numObservations = 0;
    std::cout << "Creature type '" << creatureType << "' created with description: " << description << std::endl;
}

void addSpecies(const std::string& creatureType, const std::string& species, const std::string& description) {
    creatures[creatureType].species[species].description = description;
    creatures[creatureType].species[species].numObservations = 0;
    std::cout << "Species '" << species << "' created for creature type '" << creatureType << "' with description: " << description << std::endl;
}

void searchCreatureType(const std::string& searchCreatureType) {
    auto creatureIt = creatures.find(searchCreatureType);
    if (creatureIt != creatures.end()) {
        std::cout << "Type of creature: " << creatureIt->first;
        if (!creatureIt->second.description.empty()) {
            std::cout << " - " << creatureIt->second.description;
        }
        std::cout << std::endl;

        if (!creatureIt->second.species.empty()) {
            for (const auto& species : creatureIt->second.species) {
                std::cout << "  Species: " << species.first;
                if (!species.second.description.empty()) {
                    std::cout << " - " << species.second.description;
                }
                std::cout << " (Observations: " << species.second.numObservations << ")" << std::endl;

                if (!species.second.sightings.empty()) {
                    std::cout << "  Sightings:" << std::endl;
                    for (const auto& sighting : species.second.sightings) {
                        std::cout << "    - " << sighting << std::endl;
                    }
                } else {
                    std::cout << "  No sightings for this species." << std::endl;
                }
            }
        } else {
            std::cout << "No species for this creature type." << std::endl;
        }

        std::cout << "Total Observations for " << creatureIt->first << ": " << creatureIt->second.numObservations << std::endl;
    } else {
        std::cout << "Creature type '" << searchCreatureType << "' not found." << std::endl;
    }
}

void searchSpecies(const std::string& creatureType, const std::string& searchSpecies) {
    auto creatureIt = creatures.find(creatureType);
    if (creatureIt != creatures.end()) {
        auto speciesIt = creatureIt->second.species.find(searchSpecies);
        if (speciesIt != creatureIt->second.species.end()) {
            std::cout << "Type of creature: " << creatureIt->first;
            if (!creatureIt->second.description.empty()) {
                std::cout << " - " << creatureIt->second.description;
            }
            std::cout << std::endl;

            std::cout << "  Species: " << speciesIt->first;
            if (!speciesIt->second.description.empty()) {
                std::cout << " - " << speciesIt->second.description;
            }
            std::cout << " (Observations: " << speciesIt->second.numObservations << ")" << std::endl;

            if (!speciesIt->second.sightings.empty()) {
                std::cout << "  Sightings:" << std::endl;
                for (const auto& sighting : speciesIt->second.sightings) {
                    std::cout << "    - " << sighting << std::endl;
                }
            } else {
                std::cout << "  No sightings for this species." << std::endl;
            }

            std::cout << "Total Observations for " << creatureIt->first << " - " << speciesIt->first << ": " << speciesIt->second.numObservations << std::endl;
        } else {
            std::cout << "Species '" << searchSpecies << "' not found for creature type '" << creatureType << "'." << std::endl;
        }
    } else {
        std::cout << "Creature type '" << creatureType << "' not found." << std::endl;
    }
}

void viewTotalObservations() {
    std::cout << "Total Observations: " << totalObservations << std::endl;
    }
};

int main() {
    App app;

    while (true) {
        std::cout << "\nApp Menu:" << std::endl;
        std::cout << "1. Add Sighting" << std::endl;
        std::cout << "2. View Sightings" << std::endl;
        std::cout << "3. Add Creature Type" << std::endl;
        std::cout << "4. Add Species" << std::endl;
        std::cout << "5. Search Creature Type" << std::endl;
        std::cout << "6. Search Species" << std::endl;
        std::cout << "7. View Total Observations" << std::endl;
        std::cout << "8. Exit" << std::endl;

        int choice;
        std::cout << "Enter your choice (1/2/3/4/5/6/7/8): ";
        std::cin >> choice;

        switch (choice) {
          case 1: {
            std::string username, creatureType, species, sightingText;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter the type of creature for your sighting: ";
            std::cin >> creatureType;
            std::cout << "Enter the species for your sighting: ";
            std::cin >> species;
            std::cout << "Enter your sighting details: ";
            std::cin.ignore();  // Clear the input buffer
            std::getline(std::cin, sightingText);
            app.addSighting(username, creatureType, species, sightingText);
            break;
          }
          case 2:
            app.viewSightings();
            break;
          case 3: {
            std::string creatureType, description;
            std::cout << "Enter the type of creature: ";
            std::cin >> creatureType;
            std::cout << "Enter a description for the creature type: ";
            std::cin.ignore();  // Clear the input buffer
            std::getline(std::cin, description);
            app.addCreatureType(creatureType, description);
            break;
          }
          case 4: {
            std::string creatureType, species, description;
            std::cout << "Enter the type of creature: ";
            std::cin >> creatureType;
            std::cout << "Enter the species: ";
            std::cin >> species;
            std::cout << "Enter a description for the species: ";
            std::cin.ignore();  // Clear the input buffer
            std::getline(std::cin, description);
            app.addSpecies(creatureType, species, description);
            break;
          }
          case 5: {
            std::string searchCreatureType;
            std::cout << "Enter the type of creature to search: ";
            std::cin >> searchCreatureType;
            app.searchCreatureType(searchCreatureType);
            break;
          }
          case 6: {
            std::string creatureType, searchSpecies;
            std::cout << "Enter the type of creature to search: ";
            std::cin >> creatureType;
            std::cout << "Enter the species to search: ";
            std::cin >> searchSpecies;
            app.searchSpecies(creatureType, searchSpecies);
            break;
          }
          case 7:
            app.viewTotalObservations();
            break;
          case 8:
            std::cout << "Exiting the App. Goodbye!" << std::endl;
            return 0;
          default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
