#pragma once
#include <vector>
#include <list>
#include "gcable_object.h"

namespace gc
{
    //singleton marking table
    class __GCTable
    {
    private:
        __GCTable()
        {}
    public:
        static __GCTable &get_object()
        {
            static __GCTable table;
            return table;
        }

        //트리
        struct node_type
        {
            GCableObject &self;
            std::vector<node_type &> childs;
        public:
            node_type(GCableObject &v) : self(v)
            {}
        };

        std::list<node_type> roots;
        std::list<GCableObject&> heap;

    private:
        void mark()
        {
            for (auto &root : roots)
            {
                root.self._marked = true;
                mark_recursion(root);
            }
        }
        void mark_recursion(node_type &root)
        {
            for (auto &e : root.childs)
            {
                e.self._marked = true;
                for (auto &child : e.childs)
                    mark_recursion(child);
            }
        }
        void sweep()
        {
            for (auto it = heap.begin(); it != heap.end(); it++)
            {
                if (it->marked)
                {
                    it->marked = false;
                }
                else
                {
                    puts("삭제됨");
                    it->clear();
                    it = heap.erase(it);
                }
            }
        }

    public: // public methods
        void mark_and_sweep()
        {
            mark();
            sweep();
        }

        void add(GCableObject& ptr) //마크 추가
        {
            heap.push_back(ptr);
            roots.push_back(heap.back());
        }
    };

    __GCTable &table = __GCTable::get_object();
}