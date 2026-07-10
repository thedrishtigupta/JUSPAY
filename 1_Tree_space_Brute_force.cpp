

#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    Node* parent;
    vector<Node*> children;
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

    bool hasLockedAncestor(Node* node) { // TC : O(n)
        Node* curr = node->parent;

        while(curr) {
            if(curr->isLocked) return true;
            curr = curr->parent;
        }

        return false;
    }

    bool hasLockedDesc(Node* node) { // O(h)
        for(Node* ch : node->children) {
            if(ch->isLocked) return true;
            if(hasLockedDesc(ch)) return true;
        }
        return false;
    }

    void getLockedDesc(Node* node, vector<Node*>& lockedNodes) { // sc = O(n), tc = O(n)
        for(Node* ch : node->children) {
            if(ch->isLocked) lockedNodes.push_back(ch);
            getLockedDesc(ch, lockedNodes);
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
    bool lock(string name, int uid) { // O(logmN + N) = O(N)
        Node* node = mp[name];

        if(node->isLocked) return false; // O(1)
        if(hasLockedancestor(node)) return false; // O(h)
        if(hasLockedDesc(node)) return false; // O(n) if node = 0, check every node

        node->isLocked = true;
        node->lockedBy = uid;
        return true;
    }

    bool unlock(string name, int uid) { // O(1)
        Node* node = mp[name];
        if(!node->isLocked) return false; // O(1)
        if(node->lockedBy != uid) return false; // O(1)

        node->isLocked = false;
        node->lockedBy = -1;
        return true;
    }

    bool upgrade(string name, int uid) { // O(N)
        Node* node = mp[name];

        if(node->isLocked) return false; // O(1)
        if(hasLockedAncestors(node)) return false; // O(h)

        vector<Node*> lockedNodes; // sc = O(n)
        getLockedDesc(node, lockedNodes); // O(n)

        if(lockedNodes.empty()) return false; // O(1)

        for(Node* x : lockedNodes) { //O(N)
            if(x->lockedBy != uid) return false;
        }

        for(Node* x : lockedNodes) { // O(N)
            x->isLocked = false;
            x->lockedBy = -1;
        }

        node->isLocked = true;
        node->lockedBy = uid;
        return true;
    }
};

int main() {
    int n, m , q; cin >>n>>m>>q;

    vector<string> nodes(n);
    for(int i = 0; i < n; i++) cin>>nodes[i];

    LockingTree tree(node[0]);
    tree.buildTree(nodes, m);

    while(q--) {
        int op, uid; string name;

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
TC : O(N), SC : O(N)

Why not good?
Imagine n = 5 X 10^5 and q = 5 X 10^5
No. of operations = 2.5 X 10^11

Optimization : Since ancestor check if balanced, and descendant check is traversing
subtree everytime, use something to avoid checks.
*/