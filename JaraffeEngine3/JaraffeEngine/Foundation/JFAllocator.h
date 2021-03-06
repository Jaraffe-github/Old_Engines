#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFAllocator
	{
		enum { 
			InitialHeapSize = 1 << 25, 
			MinUnitSize = 16,
			MaxUnitSize = 1 << 15, 
			AlignmentUnitSize = 16
		};

	public:
		void* Alloc(size_t);
		void* ReAlloc(void*, size_t);
		void Free(void*);

		static JFAllocator& DefaultAllocator();

	private:
		JFAllocator(void);
		JFAllocator(const JFAllocator&) = delete;
		~JFAllocator();
		JFAllocator& operator = (const JFAllocator&) = delete;

		void Init();
	};

	struct JFDefaultAllocator
	{
		static void* Alloc(size_t s) { return JFAllocator::DefaultAllocator().Alloc(s); }
		static void* Realloc(void* p, size_t s) { return JFAllocator::DefaultAllocator().ReAlloc(p, s); }
		static void Free(void* p) { JFAllocator::DefaultAllocator().Free(p); }
	};
}
