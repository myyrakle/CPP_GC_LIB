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

        //할당된 객체타입
        struct object_type
        {
            void *self;
            bool marked = false;
            object_type(void *p) : self(p)
            {
            }
        };
        //트리
        struct node_type
        {
            object_type &self;
            std::vector<node_type &> childs;

        public:
            node_type(object_type &v) : self(v)
            {
            }
        };

        std::list<node_type> roots;
        std::list<GCableObject&> heap;

    private:
        void mark()
        {
            for (auto &root : roots)
            {
                root.self.marked = true;
                mark_recursion(root);
            }
        }
        void mark_recursion(node_type &root)
        {
            for (auto &root : roots)
            {
                root.self.marked = true;
                for (auto &child : root.childs)
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

    public:
        void mark_and_sweep()
        {
            mark();
            sweep();
        }

        void add(void *ptr) //마크 추가
        {
            heap.emplace_back(ptr);
            roots.emplace_back(heap.back());
        }
    };
    static __GCTable &table = __GCTable::get_object();
}