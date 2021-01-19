/* ******************************************************
 * Name: Brock Humblet
 * Wisc ID: 9081001860
 * OS: Mac OS
 * IDE (or text editor): Clion
 * Compiler: Terminal
 * How long did the assignment take you to complete in minutes: 150
 * What other resources did you consult (copy and paste links below):
 * http://www.cplusplus.com/reference/set/set/
 * https://www.cplusplus.com/reference/map/map/
 */ // ******************************************************
#include <iostream>
#include <map>
#include <set>

using namespace std;

/*
Notes:
	1. Do not modify the names of any templated classes or functions.
		- Custom classes and functions may be added as part of the solution,
		  however, the tests will be run against the templated classes / functions
	2. If you find an error in this script, please post in piazza.
	3. Compile and run this file on the CSL machines before your final submission.
*/

/* Start Test Methods */
void Test_Show_Ship_Manifest();
void Test_Drop_Off_Passengers();
void Test_Combine_Manifests();
void Test_Get_Passengers_Overlapping_Desired_Destinations();
/* End Test Methods */

/* Prototypes for the functions you will write */
string Show_Ship_Manifest(map<string, set<string> > ship_manifest);
map<string, set<string> > Drop_Off_Passengers(map<string, set<string> > ship_manifest, set<string> passengers);
map<string, set<string> > Combine_Manifests(map<string, set<string> > ship_manifest, map<string, set<string> > other_ship_manifest);
set<string> Get_Passengers_Overlapping_Desired_Destinations(map<string, set<string> > ship_manifest, set<string> passengers);

/**
 * Runs all test cases against code
 * @return exit code
 */
int main() {
    Test_Show_Ship_Manifest();
    Test_Drop_Off_Passengers();
    Test_Combine_Manifests();
    Test_Get_Passengers_Overlapping_Desired_Destinations();
    return 0;
}

/**
 * This function formats a given ship manifest.
 *
 * @param ship_manifest mapping of passengers to the planets each passenger wants to visit.
 * @return A string representing the ship manifest.
 */
string Show_Ship_Manifest(map<string, set<string> > ship_manifest) {
    string output = "{";
    if(!ship_manifest.empty()) {
        for (auto it = ship_manifest.begin(); it != ship_manifest.end(); it++) { // iterates through maniefest map
            string destination = "{";
            if (!it->second.empty()) { // if the set string is empty in the current iteration
                for (auto itTwo : it->second) { // iterates through the current set string
                    destination += itTwo + ", ";
                }
            }
            destination = destination.substr(0, destination.size() - 2);
            destination += "}";
            output += it->first + ": " + destination + ", ";

        }
        output = output.substr(0, output.size()-2);
    }
    output += "}";
    return output;
}

/**
 * This function removes passengers from a ship's manifest. If a passenger to remove is not on the manifest, do nothing for that passenger and continue removing the other passengers.
 *
 * @param ship_manifest mapping of passengers to the planets each passenger wants to visit.
 * @param passengers set of passengers to remove from the ship manifest.
 * @return A new ship manifest mapping that does not contain any of the removed passengers.
 */
map<string, set<string> > Drop_Off_Passengers(map<string, set<string> > ship_manifest, set<string> passengers) {
    map<string, set<string> > updatedManifest = ship_manifest;
    for(auto it : passengers){ // iterates through the passengers set
        if(updatedManifest.find(it) != updatedManifest.end()) { // if it finds the passenger in the manifest
            updatedManifest.erase(it);
        }
    }
    return updatedManifest;
}

/**
 * This function combines the manifests of 2 ships. These ships CAN have the same passengers that CAN have different desired planets.
 *
 * @param ship_manifest mapping of passengers to the planets each passenger wants to visit.
 * @param other_ship_manifest mapping of passengers to the planets each passenger wants to visit.
 * @return A new ship manifest mapping that contains the union of passengers and their destinations from both ships.
 */
map<string, set<string> > Combine_Manifests(map<string, set<string> > ship_manifest, map<string, set<string> > other_ship_manifest) {
    map<string, set<string> > updatedManifest = ship_manifest;
    for(auto it : other_ship_manifest){ // iterates through second manifest
        if(updatedManifest.find(it.first) != updatedManifest.end()){ // if the manifest already contains a specific person
            auto pair = updatedManifest.find(it.first);
            for(auto itTwo : it.second){ // iterates through the set of the current iteration
                if(updatedManifest.find(it.first)->second.find(itTwo) == pair->second.end()){ // if the original manifest doesn't contain a specific destination
                    updatedManifest.find(it.first)->second.insert(itTwo);
                }
            }
        } else{
            updatedManifest.insert(it);
        }
    }
    return updatedManifest;
}

/**
 * This function gets overlapping desired destinations for a group of passengers
 *
 * @param ship_manifest mapping of passengers to the planets each passenger wants to visit.
 * @param passengers set of passengers
 * @return A set of destinations that each of the passengers in the group share
 */
set<string> Get_Passengers_Overlapping_Desired_Destinations(map<string, set<string> > ship_manifest, set<string> passengers) {
    set<string> locations;
    set<string> sharedLocations;
    if(!ship_manifest.empty()) {
        for (auto it : passengers) { // iterates through passengers set
            if(ship_manifest.find(it) == ship_manifest.end()) { // if a passenger can't be found
                return{};
            }
            if (passengers.size() == 1) {
                return ship_manifest.find(it)->second;
            } else {
                auto astronaut = ship_manifest.find(it)->second;
                if(locations.empty()){
                    locations = astronaut;
                } else {
                    for (auto itTwo : astronaut) { // iterates through current set
                        if (locations.find(itTwo) != locations.end()) { // if the current set locations match with previous locations add them to the sharedLocations set
                            sharedLocations.insert(itTwo);
                        }
                    }
                    locations = sharedLocations;
                    sharedLocations.clear();
                }
            }
        }
    }
    return locations;
}

/*

	The Below Functions Are For Testing Purposes Only

*/

template<typename T1, typename T2>
void Assert_With_Message(string test_name, T1 v1, T2 v2) {
    cout << endl << "Test ";
    if (v1 != v2) {
        cout << "Failed: " << test_name << endl;
        cout << v1 << " != " << v2 << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Passed: " << test_name << endl;
    }
}

string Show_Set(set<string> my_set) {
    string res = "{";

    int i = 0;
    for(auto const& el: my_set) {
        res = res + el;
        if(i < my_set.size() - 1) {
            res += ", ";
        }
        i += 1;
    }
    res += "}";
    return res;
}

void Test_Show_Ship_Manifest() {
    Assert_With_Message(
            "Show_Ship_Manifest - Empty Manifest",
            Show_Ship_Manifest({}),
            "{}"
    );

    Assert_With_Message(
            "Show_Ship_Manifest - One Passenger in Manifest",
            Show_Ship_Manifest(
                    {
                            {"Passenger 001", {"Venus"}},
                    }
            ),
            "{Passenger 001: {Venus}}"
    );

    Assert_With_Message(
            "Show_Ship_Manifest - One Passenger Without Destination in Manifest",
            Show_Ship_Manifest(
                    {
                            {"Passenger 001", {}},
                    }
            ),
            "{Passenger 001: {}}"
    );

    Assert_With_Message(
            "Show_Ship_Manifest - Multiple Passengers in Manifest",
            Show_Ship_Manifest(
                    {
                            {"Passenger 001", {"Venus"}},
                            {"Passenger 002", {"Earth", "Mars"}},
                            {"Passenger 003", {"Earth", "Neptune", "Pluto"}}
                    }
            ),
            "{Passenger 001: {Venus}, Passenger 002: {Earth, Mars}, Passenger 003: {Earth, Neptune, Pluto}}"
    );
}
void Test_Drop_Off_Passengers() {
    Assert_With_Message(
            "Drop_Off_Passengers - Empty Manifest, Empty Passenger",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {},
                            {}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Drop_Off_Passengers - Remove One Passenger from Empty Manifest",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {},
                            {"Passenger 001"}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Drop_Off_Passengers - Remove One Passenger from Manifest",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {
                                    {"Passenger 001", {}}
                            },
                            {"Passenger 001"}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Drop_Off_Passengers - Remove One Passenger from Manifest",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {
                                    {"Passenger 001", {"Venus"}},
                                    {"Passenger 002", {"Earth", "Mars"}},
                                    {"Passenger 003", {"Earth", "Neptune", "Pluto"}}
                            },
                            {"Passenger 003"}
                    )
            ),
            "{Passenger 001: {Venus}, Passenger 002: {Earth, Mars}}"
    );
    Assert_With_Message(
            "Drop_Off_Passengers - Remove Two Passengers from Manifest",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {
                                    {"Passenger 001", {"Venus"}},
                                    {"Passenger 002", {"Earth", "Mars"}},
                                    {"Passenger 003", {"Earth", "Neptune", "Pluto"}}
                            },
                            {"Passenger 002", "Passenger 003"}
                    )
            ),
            "{Passenger 001: {Venus}}"
    );
    Assert_With_Message(
            "Drop_Off_Passengers - Remove Two Passengers from Manifest with 2 Unremoved",
            Show_Ship_Manifest(
                    Drop_Off_Passengers(
                            {
                                    {"Passenger 001", {"Venus"}},
                                    {"Passenger 002", {"Earth", "Mars"}},
                                    {"Passenger 003", {"Earth", "Neptune", "Pluto"}}
                            },
                            {"Passenger 002", "Passenger 003", "Passenger 004", "Passenger 005"}
                    )
            ),
            "{Passenger 001: {Venus}}"
    );
}

void Test_Combine_Manifests() {
    Assert_With_Message(
            "Combine_Manifests - Empty Manifests",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {},
                            {}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Combine_Manifests - One Empty Manifest",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {
                                    {"Passenger 001", {"Venus"}}
                            },
                            {}
                    )
            ),
            "{Passenger 001: {Venus}}"
    );
    Assert_With_Message(
            "Combine_Manifests - One Empty Manifest (2)",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {},
                            {
                                    {"Passenger 001", {"Venus"}}
                            }
                    )
            ),
            "{Passenger 001: {Venus}}"
    );
    Assert_With_Message(
            "Combine_Manifests - Manifests With Unshared Passengers",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {
                                    {"Passenger 001", {"Venus"}}
                            },
                            {
                                    {"Passenger 002", {"Venus"}}
                            }
                    )
            ),
            "{Passenger 001: {Venus}, Passenger 002: {Venus}}"
    );
    Assert_With_Message(
            "Combine_Manifests - Manifests With Shared Passengers",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {
                                    {"Passenger 001", {"Venus", "Neptune"}}
                            },
                            {
                                    {"Passenger 001", {"Venus", "Mars"}}
                            }
                    )
            ),
            "{Passenger 001: {Mars, Neptune, Venus}}"
    );
    Assert_With_Message(
            "Combine_Manifests - Manifests With Shared and Unshared Passengers",
            Show_Ship_Manifest(
                    Combine_Manifests(
                            {
                                    {"Passenger 001", {}},
                                    {"Passenger 002", {"Neptune"}},
                                    {"Passenger 003", {"Pluto"}},
                                    {"Passenger 004", {"Saturn"}}
                            },
                            {
                                    {"Passenger 001", {"Venus"}},
                                    {"Passenger 002", {}},
                                    {"Passenger 003", {"Mars"}},
                                    {"Passenger 005", {"Jupiter"}}
                            }
                    )
            ),
            "{Passenger 001: {Venus}, Passenger 002: {Neptune}, Passenger 003: {Mars, Pluto}, Passenger 004: {Saturn}, Passenger 005: {Jupiter}}"
    );
}

void Test_Get_Passengers_Overlapping_Desired_Destinations() {
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Empty Manifest, Empty Passengers",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {},
                            {}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Empty Manifest, Non-Empty Passengers",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {},
                            {"Passenger 001"}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Non-Empty Manifest, Empty Passengers",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {}},
                            },
                            {}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - 1 Passenger In Manifest",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {"Venus"}},
                            },
                            {"Passenger 001"}
                    )
            ),
            "{Venus}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - 1 Passenger Not In Manifest",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {}},
                            },
                            {"Passenger 002"}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With No Overlap",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {"Venus"}},
                                    {"Passenger 002", {"Mars"}},
                                    {"Passenger 003", {"Neptune"}},
                                    {"Passenger 004", {"Pluto"}},
                                    {"Passenger 005", {"Mercury"}},
                                    {"Passenger 006", {"Uranus"}},
                                    {"Passenger 007", {"Jupiter"}},
                                    {"Passenger 008", {"Saturn"}},
                                    {"Passenger 009", {"Earth"}}
                            },
                            {"Passenger 001", "Passenger 009"}
                    )
            ),
            "{}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With Overlap",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {"Venus", "Earth"}},
                                    {"Passenger 002", {"Mars", "Earth"}},
                                    {"Passenger 003", {"Neptune"}},
                                    {"Passenger 004", {"Pluto"}},
                                    {"Passenger 005", {"Mercury", "Earth"}},
                                    {"Passenger 006", {"Uranus", "Earth"}},
                                    {"Passenger 007", {"Jupiter"}},
                                    {"Passenger 008", {"Saturn"}},
                                    {"Passenger 009", {"Earth", "Mars"}}
                            },
                            {"Passenger 001", "Passenger 002", "Passenger 005", "Passenger 009"}
                    )
            ),
            "{Earth}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With Multiple Overlap",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {"Venus", "Earth"}},
                                    {"Passenger 002", {"Mars", "Earth", "Venus"}},
                                    {"Passenger 003", {"Neptune"}},
                                    {"Passenger 004", {"Pluto"}},
                                    {"Passenger 005", {"Mercury", "Earth", "Venus"}},
                                    {"Passenger 006", {"Uranus", "Earth", "Venus"}},
                                    {"Passenger 007", {"Jupiter"}},
                                    {"Passenger 008", {"Saturn"}},
                                    {"Passenger 009", {"Earth", "Mars", "Venus"}}
                            },
                            {"Passenger 001", "Passenger 002", "Passenger 005", "Passenger 009"}
                    )
            ),
            "{Earth, Venus}"
    );
    Assert_With_Message(
            "Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With One Group Member Missing",
            Show_Set(
                    Get_Passengers_Overlapping_Desired_Destinations(
                            {
                                    {"Passenger 001", {"Venus", "Earth"}},
                                    {"Passenger 002", {"Mars", "Earth", "Venus"}},
                                    {"Passenger 003", {"Neptune"}},
                                    {"Passenger 004", {"Pluto"}},
                                    {"Passenger 005", {"Mercury", "Earth", "Venus"}},
                                    {"Passenger 006", {"Uranus", "Earth", "Venus"}},
                                    {"Passenger 007", {"Jupiter"}},
                                    {"Passenger 008", {"Saturn"}},
                                    {"Passenger 009", {"Earth", "Mars", "Venus"}}
                            },
                            {"Passenger 001", "Passenger 002", "Passenger 005", "Passenger ???"}
                    )
            ),
            "{}"
    );
}
