#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;

    Node* parent;

    vector<Node*> children;

    bool isLocked;
    int lockedBy;

    set<Node*> lockedDesc;

    Node(string n, Node* p = nullptr) : name(n), parent(p), isLocked(false), lockedBy(-1) {}
};

class LockingTree {

private:

    Node* root;

    unordered_map<string, Node*> mp;

    void updateAncestors(Node* node) {

        Node* curr = node->parent;

        while(curr) {

            curr->lockedDesc.insert(node);

            curr = curr->parent;
        }
    }

    void removeFromAncestors(Node* node) {

        Node* curr = node->parent;

        while(curr) {

            curr->lockedDesc.erase(node);

            curr = curr->parent;
        }
    }

public:

    LockingTree(string rootName) {

        root = new Node(rootName);

        mp[rootName] = root;
    }

    void buildTree(vector<string>& nodes, int m) {

        queue<Node*> q;

        q.push(root);

        int idx = 1;

        while(!q.empty() && idx < nodes.size()) {

            Node* curr = q.front();
            q.pop();

            for(int i = 0;
                i < m && idx < nodes.size();
                i++, idx++) {

                Node* child = new Node(nodes[idx], curr);

                curr->children.push_back(child);

                mp[nodes[idx]] = child;

                q.push(child);
            }
        }
    }

    bool lock(string nodeName, int uid) {

        Node* node = mp[nodeName];

        if(node->isLocked)
            return false;

        if(!node->lockedDesc.empty())
            return false;

        Node* curr = node->parent;

        while(curr) {

            if(curr->isLocked)
                return false;

            curr = curr->parent;
        }

        node->isLocked = true;
        node->lockedBy = uid;

        updateAncestors(node);

        return true;
    }

    bool unlock(string nodeName, int uid) {

        Node* node = mp[nodeName];

        if(!node->isLocked)
            return false;

        if(node->lockedBy != uid)
            return false;

        removeFromAncestors(node);

        node->isLocked = false;
        node->lockedBy = -1;

        return true;
    }

    bool upgrade(string nodeName, int uid) {

        Node* node = mp[nodeName];

        if(node->isLocked)
            return false;

        if(node->lockedDesc.empty())
            return false;

        for(Node* desc : node->lockedDesc) {

            if(desc->lockedBy != uid)
                return false;
        }

        vector<Node*> toUnlock(
            node->lockedDesc.begin(),
            node->lockedDesc.end()
        );

        for(Node* desc : toUnlock) {

            removeFromAncestors(desc);

            desc->isLocked = false;
            desc->lockedBy = -1;
        }

        node->isLocked = true;
        node->lockedBy = uid;

        updateAncestors(node);

        return true;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;
    int q;

    cin >> n >> m >> q;

    vector<string> nodes(n);

    for(int i = 0; i < n; i++) {

        cin >> nodes[i];
    }

    LockingTree tree(nodes[0]);

    tree.buildTree(nodes, m);

    while(q--) {

        int operation;
        string nodeName;
        int uid;

        cin >> operation >> nodeName >> uid;

        bool ans = false;

        if(operation == 1) {

            ans = tree.lock(nodeName, uid);

        } else if(operation == 2) {

            ans = tree.unlock(nodeName, uid);

        } else {

            ans = tree.upgrade(nodeName, uid);
        }

        cout << (ans ? "true" : "false") << "\n";
    }

    return 0;
}