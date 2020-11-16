#pragma once
enum Message_Types {
    formal, semiformal, informal
};

class Message {
private:
    int from;
    int to;
    Message_Types type;
    int size;
public:
    Message();
    void MessageCreator(int start, int end);
    int GetSize();
    Message_Types GetType();
    int GetStart();
    int GetEnd();

};


#include "Network.h"
#include <random>
using namespace std;

Network::Network() {
    int num_of_serv = rand() % 7 + 4;

    for (int i = 0; i < num_of_serv; ++i) {
        Server* a = new Server;
        a->SetIndex(i);
        all_servers.push_back(a);
    }
    SetConnections();

}

void Network::SetConnections() {
    for (int i = 0; i < all_servers.size(); ++i) {
        for (int j = i + 1; j < all_servers.size(); ++j) {
            int decider = rand() % 2;
            if (decider) {
                int speed = rand() % 200 + 1;
                Server* a = all_servers[i];
                Server* b = all_servers[j];
                a->CreateConnection(speed, b);
                b->CreateConnection(speed, a);

            }
        }

    }
}

int Network::SumMessages() {
    int sum = 0;
    for (int i = 0; i < all_servers.size(); ++i) {
        sum += all_servers[i]->GetSizeMemory();
    }
    return sum;
}


Network::Way_n_Speed Network::Tree_Searching(int start, int end, vector<bool>& visited) {
    Way_n_Speed res;

    if (start == end) {
        res.speed = 0;
        res.way.push_back(start);
        return res;
    }

    visited[start] = true;
    bool Has_Ending = false;
    res.speed = all_servers.size() * 200;
    for (int i = 0; i < all_servers[start]->neighbours.size(); ++i) {
        if (visited[all_servers[start]->neighbours[i].neighbouring_server->GetIndex()])
            continue;
        Way_n_Speed temp = Tree_Searching(all_servers[start]->neighbours[i].neighbouring_server->GetIndex(), end, visited);
        if (temp.speed != -1)
        {
            Has_Ending = true;
            if (temp.speed == 0) {
                if (res.speed > all_servers[start]->neighbours[i].speed)
                {
                    res = temp;
                    res.speed += all_servers[start]->neighbours[i].speed;
                }
            }
            else if (res.speed > (1.0 / temp.speed) + 1 / all_servers[start]->neighbours[i].speed)
            {
                res = temp;
                res.speed += all_servers[start]->neighbours[i].speed;
            }
        }
    }
    if (!Has_Ending)
    {
        res.speed = -1;
        return res;
    }
    vector<int>::iterator iterator;
    iterator = res.way.begin();
    res.way.insert(iterator, start);
    return res;








}

vector<int> Network::FindTheWay(int start, int end) {
    vector<int> result;
    vector<bool> visited;
    for (int i = 0; i < all_servers.size(); ++i) {
        visited.push_back(false);
    }

    Way_n_Speed temp = Tree_Searching(start, end, visited);
    if (temp.speed != -1)
        return temp.way;
    else
        return result;

}

void Network::GenerateNewMessage() {
    int decider = rand() % 2;
    if (!decider) {
        return;
    }
    int i_server = rand() % all_servers.size();
    int j_server = rand() % all_servers.size();
    if (i_server == j_server) {
        return;
    }
    Message* message = new Message;
    message->MessageCreator(i_server, j_server);
    vector<int> way = FindTheWay(i_server, j_server);
    if (way.size() == 0)
        return;
    Transit_Message new_message;
    new_message.TransitMessageCreator(message, way);
    Server* a = all_servers[i_server];
    a->ReceiveMessage(new_message);

}



void Network::ClearAllContent() {}

void Network::TurnOffServersWithType(Message_Types type) {}

void Network::UpdateAllServers() {
    for (int i = 0; i < all_servers.size(); ++i) {
        all_servers[i]->UpdateServer();
    }
}

void Network::Start() {
    int size_of_all_messages = 0;
    int time = 0;
    while (time < FULL_WORKING_TIME) {
        GenerateNewMessage();
        UpdateAllServers();
        size_of_all_messages = SumMessages();
        if (size_of_all_messages > OVERLOAD_VAL) {
            ClearAllContent();
        }
        time++;
    }
    TurnOffServersWithType(BANNING_TYPE_OF_LETTERS);
    Experiment();
}

class Program {
public:
    void UpdateProgram(vector<Transit_Message>& transit);
    void SendMessage(vector<Transit_Message>& transit);
    void ReceiveMessage(vector<Transit_Message>& transit);
};

void Program::UpdateProgram(vector<Transit_Message>& transit) {

}

void Program::ReceiveMessage(vector<Transit_Message>& transit) {
    if (!transit.empty())
        transit.pop_back();
}

void Program::SendMessage(vector<Transit_Message>& transit) {
    if (!transit.empty())
        transit.pop_back();
}

class Transit_Message {
private:
    Message* message;
    vector<int> way;
    int here_we_are = 0;
    int time_to_change_server;
    bool IsWaiting = true;

public:
    void TransitMessageCreator(Message* m, vector<int> n_way);

public:
    void ChangeServer();
    int NextServer();
    void ReduceWaiting();

public:
    void SetWaiting(bool flag);
    bool GetWaiting();

public:
    Message GetMessage();
    void SetTimeToChangeServer(int time);

    int GetTimeToChangeServer();


};

void Transit_Message::TransitMessageCreator(Message* m, vector<int> n_way) {
    message = m;
    way = n_way;
}

Message Transit_Message::GetMessage() {
    return *message;
}

void Transit_Message::ReduceWaiting() {
    time_to_change_server--;
}

int Transit_Message::NextServer() {
    return way[here_we_are + 1];
}

void Transit_Message::ChangeServer() {
    here_we_are++;
}

void Transit_Message::SetTimeToChangeServer(int time) {
    time_to_change_server = time;
}

int Transit_Message::GetTimeToChangeServer() {
    return time_to_change_server;
}

void Transit_Message::SetWaiting(bool flag) {
    IsWaiting = flag;
}

bool Transit_Message::GetWaiting() {
    return IsWaiting;
}

class Server {
private:
    int index_in_network;
    Program* program;
    vector<Message> memory;
    vector<Transit_Message> transit;
public:
    struct Connection {
        Server* neighbouring_server;
        int speed;
    };
    vector<Connection> neighbours;
private:
    void GenerateNewMessage();
    void SendMessages();
public:

    void UpdateServer();
    void ReceiveMessage(Transit_Message n_transit);
public:
    Server();
    int GetSizeMemory();
    void SetIndex(int ind);
    int GetIndex();
    void CreateConnection(int speed, Server* other);
};

Server::Server() {
    int program_type_decider = rand() % 7;
    switch (program_type_decider) {
    case 0: program = new ProgramFirstType;
    case 1: program = new ProgramSecondType;
    case 2: program = new ProgramThirdType;
    case 3: program = new ProgramForthType;
    case 4: program = new ProgramFifthType;
    case 5: program = new ProgramSixthType;
    case 6: program = new ProgramSevethType;
    }
}

int Server::GetSizeMemory() {
    int sum = 0;
    for (int i = 0; i < memory.size(); ++i) {
        sum += memory[i].GetSize();
    }
    return sum;
}

void Server::SetIndex(int ind) {
    index_in_network = ind;
}

int Server::GetIndex() {
    return index_in_network;
}

void Server::CreateConnection(int speed, Server* other) {
    Connection a;
    a.speed = speed;
    a.neighbouring_server = other;
    neighbours.push_back(a);
}



void Server::ReceiveMessage(Transit_Message n_transit) {
    if (n_transit.GetMessage().GetEnd() == index_in_network)
    {
        memory.push_back(n_transit.GetMessage());
        return;
    }

    n_transit.SetWaiting(true);
    int the_speed = 0;
    for (int i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i].neighbouring_server->GetIndex() == n_transit.NextServer())
            the_speed = neighbours[i].speed;
    }
    n_transit.SetTimeToChangeServer(n_transit.GetMessage().GetSize() / the_speed + 1);
    transit.push_back(n_transit);
    program->ReceiveMessage(transit);


}


void Server::UpdateServer() {
    SendMessages();
    program->UpdateProgram(transit);
    program->SendMessage(transit);

}

void Server::SendMessages() {
    for (int i = 0; i < transit.size(); ++i) {
        if (transit[i].GetWaiting()) {
            if (transit[i].GetTimeToChangeServer() == 0)
            {
                Server* next;
                for (int j = 0; j < neighbours.size(); ++j) {
                    if (neighbours[j].neighbouring_server->GetIndex() == transit[i].NextServer())
                        next = neighbours[j].neighbouring_server;
                }
                transit[i].ChangeServer();
                transit.erase(transit.begin() + i);
                next->ReceiveMessage(transit[i]);
            }
            else {
                transit[i].ReduceWaiting();
            }
        }
    }
}




