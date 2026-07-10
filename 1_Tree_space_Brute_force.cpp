

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

    bool hasLockedAncestor(Node* node) {
        Node* curr = node->parent;

        while(curr) {
            if(curr->isLocked) return true;
            curr = curr->parent;
        }

        return false;
    }

    bool hasLockedDesc(Node* node) {
        for(Node* ch : node->children) {
            if(ch->isLocked) return true;
            if(hasLockedDesc(ch)) return true;
        }
        return false;
    }

    void getLockedDesc(Node* node, vector<Node*>& lockedNodes) {
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

    void buildTree(vector<string>& nodes, int m) {
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
    bool lock(string name, int uid) {
        Node* node = mp[name];

        if(node->isLocked) return false;
        if(hasLockedancestor(node)) return false;
        if(hasLockedDesc(node)) return false;

        node->isLocked = true;
        node->lockedBy = uid;
        return true;
    }

    bool unlock(string name, int uid) {
        Node* node = mp[name];
        if(!node->isLocked) return false;
        if(node->lockedBy != uid) return false;

        node->isLocked = false;
        node->lockedBy = -1;
        return true;
    }

    bool upgrade(string name, int uid) {
        Node* node = mp[name];

        if(node->isLocked) return false;
        if(hasLockedAncestors(node)) return false;

        vector<Node*> lockedNodes;
        getLockedDesc(node, lockedNodes);

        if(lockedNodes.empty()) return false;

        for(Node* x : lockedNodes) {
            if(x->lockedBy != uid) return false;
        }

        for(Node* x : lockedNodes) {
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
