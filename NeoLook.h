#ifndef NEOLOOK_H
#define NEOLOOK_H
#include "FCFS.h"
#include "SJF.h"


class Processo {
    
private:
    int instante;
    int D_cpu;
    int D_disk;
    int D_rede;
    int id_;

public:

    Processo();

    Processo(int idp, int par1, int par2, int par3, int par4);

    void setInstante(int instante);
    void setD_cpu(int D_cpu);
    void setD_disk(int D_disk);
    void setD_rede(int D_rede);
    void setid_(int id);

    int getID() const;
    int getInstante();
    int getD_cpu();
    int getD_disk();
    int getD_rede();
};

class CPU {     
private:
    Fifo<int> listaFifo;
    LinkedList<int> listaSjf;

public:

    Fifo<int> getListaFifo();
    LinkedList<int> getListaSjf();

};

class Disk {
private:
    Fifo<int> listaFifo;
    LinkedList<int> listaSjf;

public:
    Fifo<int> getListaFifo();
    LinkedList<int> getListaSjf();
};

class Computador {
private:
    CPU cpu_;
    Disk disk1;
    Disk disk2;
    LinkedList<Processo> processInPc;
    bool cpuOcupada=false;
    bool disk1Ocupada=false;
    bool disk2Ocupada=false;

public:
    Computador();

    Computador(CPU cpu, Disk d1, Disk d2);

    void setCPU(int D_cpu, std::string estrutura);

    void setDisco1(int D_disk1, std::string estrutura);

    void setDisco2(int D_disk2, std::string estrutura);

    void addProcess(Processo process);

    Processo getProcesso(int id);

    LinkedList<Processo> getProcessos();

    void setCpuOcupada(Computador comp, bool uso);

    void setDisk1Ocupada(Computador comp, bool uso);

    void setDisk2Ocupada(Computador comp, bool uso);

    CPU getCPU() const;

    Disk getDisco1() const;

    Disk getDisco2() const;
};

#endif
