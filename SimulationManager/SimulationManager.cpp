//
// Created by afons on 07/10/2025.
//

#include "SimulationManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>


using namespace std;

struct Config {
    int row{};
    int col{};
    int coins{};
    int item_interval{};
    int item_duration{};
    int max_items{};
    int sell_price{};
    int buy_price{};
    int caravan_price{};
    int bandits_interval{};
    int bandits_duration{};
    std::string map;
};


SimulationManager::SimulationManager() {
    simulation = nullptr;
    render = nullptr;
    simulation_running = false;
}

SimulationManager::~SimulationManager() {
    delete render;
    delete simulation;
}

Status SimulationManager::handleConfigCommand(const string &file) {

    std::ifstream f(file);
    if (!f.is_open()) {
        return {false, "Error: could not open configuration file."};
    }

    Config cfg;
    std::string line;


    if (!std::getline(f, line)) {
        return {false, "Error: missing 'rows' line."};
    }
    {
        std::istringstream ss(line);
        std::string key; ss >> key >> cfg.row;
    }

    // Read cols
    if (!std::getline(f, line)) { return {false, "Error: missing 'col' line."}; }
    {
        std::istringstream ss(line);
        std::string key; ss >> key >> cfg.col;
    }

    if (cfg.row <= 0 || cfg.col <= 0) {
        return {false, "Error: invalid map dimensions."};
    }


    for (int i = 0; i < cfg.row; ++i) {
        std::getline(f, line);

        if (line.length() != cfg.col) {
            return {false, "Error: line " + std::to_string(i) + " has wrong number of columns."};
        }
        cfg.map += line;
    }

    while (std::getline(f, line)) {
        std::istringstream ss(line);
        std::string chave;
        int valor{};

        ss >> chave >> valor;

        if (chave == "moedas")                             cfg.coins = valor;
        else if (chave == "instantes_entre_novos_itens")   cfg.item_interval = valor;
        else if (chave == "duração_item")                  cfg.item_duration = valor;
        else if (chave == "max_itens")                     cfg.max_items = valor;
        else if (chave == "preço_venda_mercadoria")        cfg.sell_price = valor;
        else if (chave == "preço_compra_mercadoria")       cfg.buy_price = valor;
        else if (chave == "preço_caravana")                cfg.caravan_price = valor;
        else if (chave == "instantes_entre_novos_barbaros")cfg.bandits_interval = valor;
        else if (chave == "duração_barbaros")              cfg.bandits_duration = valor;
    }

    simulation = new Simulation(
            cfg.row, cfg.col, cfg.coins, cfg.item_interval, cfg.item_duration,
            cfg.max_items, cfg.sell_price, cfg.buy_price, cfg.caravan_price,
            cfg.bandits_interval, cfg.bandits_duration, cfg.map);


    render = new Render(cfg.row, cfg.col);
    simulation_running = true;

    return {true, "Simulation initialized successfully."};

}

void SimulationManager::doRender() const {

    if (simulation) {
        render->render(simulation->get_map_state(), simulation->get_simulation_info());
    } else {
        std::cerr << "Error: simulation is not initialized!\n";
    }
}

void SimulationManager::start() {
    while (true) {
        std::vector<std::string> command = handle_user_input();

        if (command.empty()) {
            render->render("No command entered.");
            continue;
        }

        if(!simulation_running) {
            if (command.size() == 1 && command[0] == "sair") {
                render->render("Releasing resources...");
                break;
            }

            if(command.size() == 2 && command[0]=="config") {
                auto s = handleConfigCommand(command[1]);
                render->render(s.message);

                if (s.ok) {
                    doRender();
                }
                continue;
            }
        }

        handle_simulation_commands(command);
    }
}


bool SimulationManager::string_to_positive_int(const std::string& s, int& out) {
    try {
        size_t pos;
        int val = std::stoi(s, &pos);
        if (pos != s.size() || val <= 0)
            return false;
        out = val;
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

void SimulationManager::handle_simulation_commands(const std::vector<std::string> &command) {

    const string& cmd = command[0];

    if (cmd == "exec") {
        if (command.size() == 2) {
            // TODO: implement exec
        } else {
            render->render("Usage: exec <filename>");
        }
    }
    else if (cmd == "prox") {
        int num = 1;
        if (command.size() == 2) {
            if (!string_to_positive_int(command[1], num)) {
                render->render("Usage: prox [n] (n must be a positive integer)");
                return;
            }
        } else if (command.size() != 1) {
            render->render("Usage: prox [n]");
            return;
        }

        for (int i = 0; i < num; ++i) {
            simulation->next_turn();
            doRender();
        }
    }
    else if (cmd == "comprac") {
        if (command.size() == 3) {
            Status status = simulation->buy_caravan(command[1], command[2]);
            render->render(status.message);
        } else {
            render->render("Usage: comprac <cityId> <caravanType>");
        }
    }
    else if (cmd == "precos") {
        if (command.size() == 1) {
            render->render(simulation->get_goods_prices());
        } else {
            render->render("Usage: precos");
        }
    }
    else if (cmd == "cidade") {
        if (command.size() == 2) {
            render->render(simulation->get_city_info(command[1]));
        } else {
            render->render("Usage: cidade <cityId>");
        }
    }
    else if (cmd == "caravana") {
        if (command.size() == 2) {
            render->render(simulation->get_caravan_info(command[1]));
        } else {
            render->render("Usage: caravana <caravanId>");
        }
    }
    else if (cmd == "compra") {
        if (command.size() == 3) {
            // TODO: implement compra
        } else {
            render->render("Usage: compra <caravanId> <resource>");
        }
    }
    else if (cmd == "vende") {
        if (command.size() == 2) {
            // TODO: implement vende
        } else {
            render->render("Usage: vende <caravanId>");
        }
    }
    else if (cmd == "move") {
        if (command.size() == 3) {
            // TODO: implement move
        } else {
            render->render("Usage: move <caravanId> <destination>");
        }
    }
    else if (cmd == "auto") {
        if (command.size() == 2) {
            // TODO: implement auto
        } else {
            render->render("Usage: auto <on|off>");
        }
    }
    else if (cmd == "barbaro") {
        if (command.size() == 3) {
            // TODO: implement barbaro
        } else {
            render->render("Usage: barbaro <cityId> <strength>");
        }
    }
    else if (cmd == "areia") {
        if (command.size() == 4) {
            // TODO: implement areia
        } else {
            render->render("Usage: areia <x> <y> <radius>");
        }
    }
    else if (cmd == "moedas") {
        if (command.size() == 2) {
            // TODO: implement moedas
        } else {
            render->render("Usage: moedas <cityId>");
        }
    }
    else if (cmd == "tripu") {
        if (command.size() == 3) {
            // TODO: implement tripu
        } else {
            render->render("Usage: tripu <caravanId> <n>");
        }
    }
    else if (cmd == "saves") {
        if (command.size() == 2) {
            // TODO: implement saves
        } else {
            render->render("Usage: saves <filename>");
        }
    }
    else if (cmd == "loads") {
        if (command.size() == 2) {
            // TODO: implement loads
        } else {
            render->render("Usage: loads <filename>");
        }
    }
    else if (cmd == "list") {
        if (command.size() == 1) {
            // TODO: implement list
        } else {
            render->render("Usage: list");
        }
    }
    else if (cmd == "dels") {
        if (command.size() == 2) {
            // TODO: implement dels
        } else {
            render->render("Usage: dels <filename>");
        }
    }
    else if (cmd == "terminar") {
        if (command.size() == 1) {
            simulation_running = false;
            doRender();
        } else {
            render->render("Usage: terminar");
        }
    }
    else {
        render->render("Unknown command: " + cmd);
    }
}


std::vector<std::string> SimulationManager::handle_user_input() {

    string line;
    getline(cin, line);

    istringstream iss(line);

    vector<string> commands;
    string aux;

    while (iss >> aux) {
        commands.push_back(aux);
    }
    return commands;
}