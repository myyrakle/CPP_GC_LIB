#pragma once
#include <vector>
#include <list>
#include "primitive.h"

namespace gc
{
    //gc 가능 인터페이스
    class GCable
    {
    public:
        virtual void clear() = 0;
    };

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
        std::list<object_type> heap;

    public:
        void mark()
        {
            for (auto &root : roots)
            {
                root.self.marked = true;
                mark_recur(root);
            }
        }
        void mark_recur(node_type &root)
        {
            for (auto &root : roots)
            {
                root.self.marked = true;
                for (auto &child : root.childs)
                    mark_recur(child);
            }
        }

        void sweep()
        {
            for (auto it = heap.begin(); it != heap.end(); it++)
            {
                if (it->marked)
                    it->marked = false;
                else
                    it = heap.erase(it);
            }
        }

        void add(void *ptr) //마크 추가
        {
            heap.emplace_back(ptr);
            roots.emplace_back(heap.back());
        }
    };
    static __GCTable &table = __GCTable::get_object();


    void collect()
    {
    }

    void clear()
    {
    }

    template <class T>
    class ptr
    {
    private:
        T *p;

    public:
        ptr(T &&value)
            : p(new T(std::forward<T &&>(value)))
        {
            table.add(p);
        }
        virtual ~ptr()
        {
        }

    public:
        ptr(const ptr &other)
        {
        }
        ptr(ptr &&other)
        {
        }
        ptr &operator=(const ptr &other)
        {
        }
        ptr &operator=(ptr &&other)
        {
        }

    public:
        T &operator*() const
        {
            return *p;
        }

        //...
    };

    template <class T>
    ptr<T> gcnew(T &&value)
    {
        return ptr<T>(std::forward<T &&>(value));
    }
    template <class T, class... Args>
    ptr<T> gcnew(Args &&... args)
    {
        return ptr<T>(T(args...));
    }
} // namespace gc