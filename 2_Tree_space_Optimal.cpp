

#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    Node* parent;
    vector<Node*> children;
    unordered_set<Node*> lockedDesc;
    bool isLocked;
    int lockedBy;

    Node(string n, Node* p = nullptr) {
        name = n; parent = p; isLocked = false; lockedBy = -1;
    }
};

class LockingTree{
    private:
    Node* root;
    unordered_map<string, Node*> mp;

    bool hasLockedAncestor(Node* node) { // TC : O(h)
        Node* curr = node->parent;

        while(curr) {
            if(curr->isLocked) return true;
            curr = curr->parent;
        }

        return false;
    }

    void addLockedDesc(Node* node) { // O(h)
        Node* curr = node->parent;

        while(curr) {
            curr->lockedDesc.insert(node);
            curr = curr->parent;
        }
    }

    void emptyLockedDesc(Node* node) { // O(h)
        Node* curr = node->parent;

        while(curr) {
            curr->lockedDesc.erase(node);
            curr = curr->parent;
        }
    }


    public:
    LockingTree(string name) {
        root = new Node(name);
        mp[name] = root;
    }

    void buildTree(vector<string>& nodes, int m) { // tc = O(n), sc = O(n) -> every node created, pushed, popped once
        queue<Node*> q;
        q.push(root);

        int n = nodes.size(), j = 1;

        while(!q.empty() && j < n) {
            Node* curr = q.front(); q.pop();

            for(int i = 0; i < m && j < n; i++, j++) {
                Node* ch = new Node(nodes[j], curr);
                curr->children.push_back(ch);
                mp[nodes[j]] = ch;
                q.push(ch);
            }
        }
    }
    bool lock(string name, int uid) { // O(h)
        Node* node = mp[name];

        if(node->isLocked) return false; // O(1)
        if(hasLockedAncestor(node)) return false; // O(h)
        if(!node->lockedDesc.empty()) return false;

        node->isLocked = true;
        node->lockedBy = uid;

        addLockedDesc(node); // O(h)

        return true;
    }

    bool unlock(string name, int uid) { // O(h)
        Node* node = mp[name];
        if(!node->isLocked) return false; // O(1)
        if(node->lockedBy != uid) return false; // O(1)

        node->isLocked = false;
        node->lockedBy = -1;

        emptyLockedDesc(node); //O(h)

        return true;
    }

    bool upgrade(string name, int uid) { // O(k.h)
        Node* node = mp[name];

        if(node->isLocked) return false; // O(1)
        if(hasLockedAncestor(node)) return false; // O(h)

        if(node->lockedDesc.empty()) return false; // O(1)

        for(Node* x : node->lockedDesc) { //O(k)
            if(x->lockedBy != uid) return false;
        }

        vector<Node*> temp(node->lockedDesc.begin(), node->lockedDesc.end());

        for(Node* x : temp) { // O(k.h)

            x->isLocked = false;
            x->lockedBy = -1;
            emptyLockedDesc(x);
        }

        node->isLocked = true;
        node->lockedBy = uid;
        addLockedDesc(node);

        return true;
    }
};

int main() {
    int n, m , q; cin >>n>>m>>q;

    vector<string> nodes(n);
    for(int i = 0; i < n; i++) cin>>nodes[i];

    LockingTree tree(nodes[0]);
    tree.buildTree(nodes, m);

    while(q--) {
        int op, uid; string name; cin>>op>>name>>uid;

        bool ans;
        if(op == 1) ans = tree.lock(name, uid);
        else if (op == 2) ans = tree.unlock(name, uid);
        else ans = tree.upgrade(name, uid);

        cout<<(ans ? "true" : "false")<<endl;
    }
    return 0;
}

/*
Given constraints:
N ≤ 5 x 10^5
Q ≤ 5 x 10^5
1 < m < 30

height = logm(n) = log30(10^5) = 13

Overall :
TC : O(k.logmN), SC : O(N)

Why not vector? Erase operation will take O(n).

*/