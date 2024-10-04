#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "FCFS.h"
#include "SJF.h"
#include "NeoLook.h"

Processo::Processo() : instante(0), D_cpu(0), D_disk(0), D_rede(0), id_(0) {}

Processo::Processo(int idp, int par1, int par2, int par3, int par4){
    id_ = idp;
    instante = par1;
    D_cpu = par2;
    D_disk = par3;
    D_rede = par4;
}

void Processo::setid_(int id){
    this->id_=id;
}

void Processo::setInstante(int instante){
    this->instante=instante;
}
void Processo::setD_cpu(int D_cpu){
    this->D_cpu=D_cpu;
}

void Processo::setD_disk(int D_disk){
    this->D_disk=D_disk;
}

void Processo::setD_rede(int D_rede){
    this->D_rede=D_rede;
}

int Processo::getID() const {
    return id_;
}

int Processo::getInstante(){
    return instante;
}

int Processo::getD_cpu(){
    return D_cpu;
}

int Processo::getD_disk(){
    return D_disk;
}

int Processo::getD_rede(){
    return D_rede;
}

Fifo<int> CPU::getListaFifo(){
    return listaFifo;
}

LinkedList<int> CPU::getListaSjf(){
    return listaSjf;
}

Fifo<int> Disk::getListaFifo(){
    return listaFifo;
}

LinkedList<int> Disk::getListaSjf(){
    return listaSjf;
}

Computador::Computador(){CPU {}, Disk {}, Disk {};}

Computador::Computador(CPU cpu, Disk d1, Disk d2) : cpu_(cpu), disk1(d1), disk2(d2) {}

void Computador::setCPU(int D_cpu, std::string estrutura){
    if (estrutura=="SJF"){
        cpu_.getListaSjf().push_back(D_cpu);
    } else {
        cpu_.getListaFifo().push(D_cpu);
    }
}

void Computador::setDisco1(int D_disk1, std::string estrutura){
    if (estrutura=="SJF"){
        disk1.getListaSjf().push_back(D_disk1);
    } else {
        disk1.getListaFifo().push(D_disk1);
    }
}

void Computador::setDisco2(int D_disk2, std::string estrutura){
    if (estrutura=="SJF"){
        disk2.getListaSjf().push_back(D_disk2);
    } else {
        disk2.getListaFifo().push(D_disk2);
    }
}

void Computador::addProcess(Processo process){
    processInPc.push_back(process);
}

Processo Computador::getProcesso(int id){
        for (Processo process : processInPc){
            if (process.getID()==id){
                return process;
            }
        }
    }

LinkedList<Processo> Computador::getProcessos(){
    return processInPc;
}

void Computador::setCpuOcupada(Computador comp, bool uso){
    cpuOcupada=uso;
}

void Computador::setDisk1Ocupada(Computador comp, bool uso){
    disk1Ocupada=uso;
}

void Computador::setDisk2Ocupada(Computador comp, bool uso){
    disk2Ocupada=uso;
}

CPU Computador::getCPU() const {
    return cpu_;
}

Disk Computador::getDisco1() const {
    return disk1;
}

Disk Computador::getDisco2() const {
    return disk2;
}


