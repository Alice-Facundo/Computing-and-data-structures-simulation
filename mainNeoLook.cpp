#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include "FCFS.h"
#include "SJF.h"
#include "NeoLook.h"


// Organiza os processos a partir do valor de D_CPU
template <typename T>
void organizarPorDCPU(LinkedList<T>& processos, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < tamanho; ++j) {
            if (processos[j].D_cpu < processos[minIndex].D_cpu) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(processos[i], processos[minIndex]);
        }
    }
}

// Retorna um computador aleatório
template <typename T>
T getRandomItem(const LinkedList<T>& computadores) {
    int listSize = computadores.size();

    if (listSize == 0) {
        throw std::runtime_error("A lista está vazia.");
    }

    std::mt19937 rng(static_cast<unsigned>(std::time(0)));
    
    std::uniform_int_distribution<int> distribution(0, listSize - 1);
    int randomIndex = distribution(rng);

    typename LinkedList<T>::Iterator it = computadores.begin();
    for (int i = 0; i < randomIndex; ++i) {
        ++it;
    }

    return *it;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso incorreto. Sintaxe: " << argv[0] << " estrutura_de_dados arquivo_de_entrada.txt" << std::endl;
        return 1;
    }

    std::string estrutura = argv[1];
    std::string arquivo_entrada = argv[2];

    // Abre o arquivo de entrada.txt
    std::ifstream arquivo(arquivo_entrada);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << arquivo_entrada << std::endl;
        return 1;
    }

    std::vector<std::string> linhas;
    std::string linha;

    // Lê cada linha do arquivo
    while (std::getline(arquivo, linha)) {
        linhas.push_back(linha);
    }

    arquivo.close();  // Fecha o arquivo

    // Variáveis de controle
    int qtd_processos = linhas.size();
    int tmp_exe = 0;
    int tmp_espera = 0;
    int tmp_process = 0;

    // Listas de processos a depender da estrutura de escalonamento
    LinkedList<Processo> processosSJF;
    Fifo<Processo> processosFCFS;

    // Listas de Redes a depender da estrutura de escalonamento
    LinkedList<int> RedeSJF;
    Fifo<int> RedeFCFS;


    // Agora você pode acessar a estrutura e as linhas do arquivo
    std::cout << "Estrutura: " << estrutura << std::endl;
    std::cout << "Arquivo de entrada: " << arquivo_entrada << std::endl;
    std::cout << "Numero de linhas no arquivo: " << linhas.size() << std::endl;

    // Para acessar os parâmetros de cada linha como inteiros
    int c=0;
    int instante, D_cpu, D_disk, D_rede;
    for (const std::string& l : linhas) {
        std::istringstream iss(l);
        Processo pro;

        if (iss >> instante >> D_cpu >> D_disk >> D_rede) {
            // Os valores foram lidos com sucesso como inteiros
            pro.setInstante(instante);
            pro.setD_cpu(D_cpu);
            pro.setD_disk(D_disk);
            pro.setD_rede(D_rede);
            pro.setid_(c);
            if (estrutura=="SJF"){
                RedeSJF.push_back(D_rede);
            } else {
                RedeFCFS.push(D_rede);
            }
            c++;
            std::cout << "instante: " << instante << ", D_cpu: " << D_cpu << ", D_disk: " << D_disk << ", D_rede: " << D_rede << std::endl;
            tmp_exe += D_cpu + D_disk + D_rede;
        } else {
            std::cerr << "Erro ao ler parâmetros da linha: " << l << std::endl;
        }

        if (estrutura=="SJF"){
            processosSJF.push_front(pro);
        } else {
            processosFCFS.push(pro);
        }
    }

    std::cout << "Quantidade de Processos: " << qtd_processos << std::endl;
    //std::cout << "Tempo de Execucao: " << tmp_exe << std::endl;

    std::cout << "Quantos computadores serão utilizados no programa?" << std::endl;
    int numComp;
    std::cin >> numComp;

    LinkedList<Computador> computadores;
    for (int i = 0; i < numComp; ++i) {
        Computador comp;
        computadores.push_front(comp);
    }

    if (estrutura=="SJF"){
        for (Processo process : processosSJF){
            // Sortear o computador
            getRandomItem(computadores).setCPU(process.getD_cpu(), "SJF");
            getRandomItem(computadores).addProcess(process);

            // Sortear os discos 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(1, 2);
            int numeroSorteado = dist(gen);

            if (numeroSorteado==1){
                getRandomItem(computadores).setDisco1(process.getD_disk(), "SJF");
            } else {
                getRandomItem(computadores).setDisco2(process.getD_disk(), "SJF");
            }

        }
    } else {
        for (Processo process : processosFCFS){
            // Sortear o computador
            getRandomItem(computadores).setCPU(process.getD_cpu(), "FCFS");
            getRandomItem(computadores).addProcess(process);

            // Sortear os discos
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(1, 2);
            int numeroSorteado = dist(gen);

            if (numeroSorteado==1){
                getRandomItem(computadores).setDisco1(process.getD_disk(), "FCFS");
            } else {
                getRandomItem(computadores).setDisco2(process.getD_disk(), "FCFS");
            }

        }
    }

    // Ordena as listas
    if (estrutura=="SJF"){
        // Ordena os valores da CPU
        for (Computador comput : computadores) {
            CPU cpu_ = comput.getCPU();
            LinkedList<int> listaCpu = cpu_.getListaSjf();
            listaCpu.sort();
            for (int d_cpu : listaCpu){
                comput.setCPU(d_cpu, "SJF");
            }
        }
        // Ordena os valores do Disco 1
        for (Computador comput : computadores) {
            Disk disk1 = comput.getDisco1();
            LinkedList<int> listaDisco1 = disk1.getListaSjf();
            listaDisco1.sort();
            for (int d_disk1 : listaDisco1){
                comput.setCPU(d_disk1, "SJF");
            }
        }
        // Ordena os valores do Disco 1
        for (Computador comput : computadores) {
            Disk disk2 = comput.getDisco2();
            LinkedList<int> listaDisco2 = disk2.getListaSjf();
            listaDisco2.sort();
            for (int d_disk2 : listaDisco2){
                comput.setCPU(d_disk2, "SJF");
            }
        }
        // Ordena os processos a partir do valor da D_cpu
        for (Computador comput : computadores) {
            LinkedList<Processo> processos = comput.getProcessos();
            organizarPorDCPU(processos, processos.size());
            processosSJF.clear();
            for (Processo process : processos){
                processosSJF.push_back(process);
            }

        }

        RedeSJF.sort();

    }

    int contador = 0;

    for (contador; true ; contador++){

        if (estrutura=="SJF"){
            // Passa os processos pela CPU
            for (Computador comput : computadores) {
               LinkedList<Processo> paraExecutar =  comput.getProcessos();
               for (Processo process : paraExecutar){
                if (process.getInstante()==contador){
                    comput.setCpuOcupada(comput,true);
                    std::cout << "Processo: " << process.getID() << " está sendo executado na CPU" << std::endl;
                    while (contador<=process.getD_cpu()){
                         contador++;  
                    }
                    comput.setCpuOcupada(comput,false);
                }
                
               }
                int aux=contador;
                // Passa os processos pelo Disco 1
                comput.setDisk1Ocupada(comput,true);
                Disk d_disks1 = comput.getDisco1();
                LinkedList<int> d_disks1Sjf = d_disks1.getListaSjf();
                for ( int d_disk1 : d_disks1Sjf ){
                    for (int i=contador; d_disk1+i>contador; contador++){
                        std::cout << "Processo está executando há: " << contador-i << " unidades de tempo no disco 1" << std::endl;
                        contador++;  
                    }
                }
                comput.setCpuOcupada(comput,false);

                for ( int d_disk1 : d_disks1Sjf ){
                    d_disks1Sjf.pop_back();
                    for (int d_disk1 : d_disks1Sjf){
                        tmp_espera+=d_disk1;
                    }
                }
                tmp_espera-=d_disks1Sjf.front();

                tmp_process+=contador;
                // Volta no tempo para simular uma execução simultânea nos dois discos
                contador=aux;

                // Passa os processos pelo Disco 2 
                comput.setDisk1Ocupada(comput,true);
                Disk d_disks2 = comput.getDisco2();
                LinkedList<int> d_disks2Sjf = d_disks2.getListaSjf();
                for ( int d_disk2 : d_disks2Sjf ){
                    for (int i=contador; d_disk2+i>contador; contador++){
                        std::cout << "Processo está executando há: " << contador-i << " unidades de tempo no disco 2" << std::endl;
                        contador++;  
                    }
                }
                comput.setCpuOcupada(comput,false);
                for ( int d_disk2 : d_disks2Sjf ){
                    d_disks1Sjf.pop_back();
                    for (int d_disk2 : d_disks2Sjf){
                        tmp_espera+=d_disk2;
                    }
                }
                tmp_espera-=d_disks2Sjf.front();

                tmp_process+=contador-aux;
            }

            for (int d_rede : RedeSJF){
                for (int i=contador; d_rede+i>contador; contador++){
                    std::cout << "Processo está executando há: " << contador-i << " unidades de tempo na rede" << std::endl;
                    contador++;  
                }
                RedeSJF.pop_front();
                std::cout << "Processo saiu da rede" << std::endl;
            }
            tmp_process+=contador-tmp_process;

            for (int d_rede : RedeSJF){
                RedeSJF.pop_back();
                for (int d_rede : RedeSJF){
                    tmp_espera+=d_rede;
                }
            }
            tmp_espera-=RedeSJF.front();


            // Voltar no tempo para simular execução simultânea dos computadores 
            contador=0;

        } else {
            // Passa os processos pela CPU
            for (Computador comput : computadores) {
               LinkedList<Processo> paraExecutar =  comput.getProcessos();
               for (Processo process : paraExecutar){
                if (process.getInstante()==contador){
                    comput.setCpuOcupada(comput,true);
                    std::cout << "Processo: " << process.getID() << " está sendo executado na CPU" << std::endl;
                    while (contador<=process.getD_cpu()){
                         contador++;  
                    }
                    comput.setCpuOcupada(comput,false);
                }
                
               }

               int aux=contador;

                    // Passa os processos pelo Disco 1
                    comput.setDisk1Ocupada(comput,true);
                    Disk d_disks1 = comput.getDisco1();
                    Fifo<int> d_disks1Fifo = d_disks1.getListaFifo();
                    for ( int d_disk1 : d_disks1Fifo ){
                        for (int i=contador; d_disk1+i>contador; contador++){
                            std::cout << "Processo está executando há: " << contador-i << " unidades de tempo no disco 1" << std::endl;
                            contador++;  
                        }
                    }
                    comput.setCpuOcupada(comput,false);

                    for ( int d_disk1 : d_disks1Fifo ){
                        d_disks1Fifo.pop();
                        for (int d_disk1 : d_disks1Fifo){
                            tmp_espera+=d_disk1;
                        }
                    }
                    tmp_espera-=d_disks1Fifo.front();

                    tmp_process+=contador;
                    // Volta no tempo para simular uma execução simultânea nos dois discos
                    contador=aux;

                    // Passa os processos pelo Disco 2
                    comput.setDisk1Ocupada(comput,true);
                    Disk d_disks2 = comput.getDisco2();
                    Fifo<int> d_disks2Fifo = d_disks2.getListaFifo();
                    for ( int d_disk2 : d_disks2Fifo ){
                        for (int i=contador; d_disk2+i>contador; contador++){
                            std::cout << "Processo está executando há: " << contador-i << " unidades de tempo no disco 2" << std::endl;
                            contador++;  
                        }
                    }
                    comput.setCpuOcupada(comput,false);

                    for ( int d_disk2 : d_disks2Fifo ){
                        d_disks1Fifo.pop();
                        for (int d_disk2 : d_disks2Fifo){
                            tmp_espera+=d_disk2;
                        }
                    }
                    tmp_espera-=d_disks2Fifo.front();
                    tmp_process+=contador-aux;

               
            }
            for (int d_rede : RedeFCFS){
                for (int i=contador; d_rede+i>contador; contador++){
                    std::cout << "Processo está executando há: " << contador-i << " unidades de tempo na rede" << std::endl;
                    contador++;  
                }
                RedeFCFS.pop();
                std::cout << "Processo saiu da rede" << std::endl;
            }
            tmp_process+=contador-tmp_process;

            for (int d_rede : RedeFCFS){
                RedeFCFS.pop();
                for (int d_rede : RedeFCFS){
                    tmp_espera+=d_rede;
                }
            }
            tmp_espera-=RedeFCFS.front();

            // Voltar no tempo para simular execução simultânea dos computadores 
            contador=0;
        }

        
    }

    if (estrutura=="SJF"){
        for (Processo process : processosSJF){
            processosSJF.pop_back();
            for(Processo process : processosSJF){
                tmp_espera+=process.getD_cpu();
            }
        }
        tmp_espera-=processosSJF.front().getD_cpu();
    } else {
        for (Processo process : processosFCFS){
            processosFCFS.pop();
            for(Processo process : processosFCFS){
                tmp_espera+=process.getD_cpu();
            }
        }
        tmp_espera-=processosFCFS.front().getD_cpu();
    }

    std::cout << "......................................................................................." << std::endl;

    std::cout << "Tempo de Execução total: " << tmp_exe << std::endl;
    std::cout << "Tempo de Execução média: " << tmp_exe/qtd_processos << std::endl;

    std::cout << "......................................................................................." << std::endl;

    std::cout << "Tempo de Espera total: " << tmp_espera << std::endl;
    std::cout << "Tempo de Espera média: " << tmp_espera/qtd_processos << std::endl;

    std::cout << "......................................................................................." << std::endl;

    std::cout << "Taxa de processamento: " << qtd_processos/tmp_process << std::endl;

    return 0;
}