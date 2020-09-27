using System;
using System.Collections.Generic;
using System.Text;

namespace Graphyte.Build.Extensions
{
    public static class ListExtensions
    {
        public static bool Import<T>(this List<T> collection, T item)
        {
            if (!collection.Contains(item))
            {
                collection.Add(item);
                return true;
            }

            return false;
        }

        public static void Import<T>(this List<T> collection, IEnumerable<T> items)
        {
            foreach (var item in items)
            {
                if (!collection.Contains(item))
                {
                    collection.Add(item);
                }
            }
        }

        public static void Import<K, V>(this Dictionary<K, V> collection, IEnumerable<KeyValuePair<K, V>> items)
        {
            foreach (var item in items)
            {
                collection[item.Key] = item.Value;
            }
        }
    }
}
