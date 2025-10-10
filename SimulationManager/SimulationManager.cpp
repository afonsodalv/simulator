//
// Created by afons on 07/10/2025.
//

#include "SimulationManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    render = Render();
    buffer = nullptr;
    simulation = nullptr;
}

SimulationManager::~SimulationManager() {
    delete buffer;
}

void SimulationManager::handleConfigCommand(const string &file) {

    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro de configuração." << std::endl;
        exit(EXIT_FAILURE);
    }

    Config cfg;
    std::string line;


    if (!std::getline(f, line)) { std::exit(EXIT_FAILURE); }
    {
        std::istringstream ss(line);
        std::string key; ss >> key >> cfg.row;
    }

    // Read cols
    if (!std::getline(f, line)) { std::exit(EXIT_FAILURE); }
    {
        std::istringstream ss(line);
        std::string key; ss >> key >> cfg.col;
    }

    if (cfg.row <= 0 || cfg.col <= 0) {
        std::cerr << "Erro: Dimensões do mapa inválidas.\n";
        std::exit(EXIT_FAILURE);
    }


    for (int i = 0; i < cfg.row; ++i) {
        std::getline(f, line);

        if (line.length() != cfg.col) {
            std::cerr << "Erro: O número de colunas da linha " << i << " não corresponde ao esperado." << std::endl;
            exit(EXIT_FAILURE);
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
        else {
            std::cerr << "Aviso: Configuração desconhecida: " << chave << "\n";
        }
    }

    simulation = new Simulation(
            cfg.row, cfg.col, cfg.coins, cfg.item_interval, cfg.item_duration,
            cfg.max_items, cfg.sell_price, cfg.buy_price, cfg.caravan_price,
            cfg.bandits_interval, cfg.bandits_duration, cfg.map);


    buffer = new Buffer(cfg.row, cfg.col);

}

void SimulationManager::doRender() {

    if (buffer && simulation) {
        render.render(simulation->get_map_state(), simulation->get_simulation_info(),*buffer);
    } else {
        std::cerr << "Error: buffer is not initialized!\n";
    }
}