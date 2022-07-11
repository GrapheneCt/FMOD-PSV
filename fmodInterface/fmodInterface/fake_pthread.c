#include <kernel.h>

#define EXPORT __declspec(dllexport)

typedef struct pthreadEntryArg
{
	void *(*func)(void *);
	void *arg;
} pthreadEntryArg;

typedef struct sched_param
{
	int sched_priority;
} sched_param;

typedef struct pthread_attr_t_ {
	char name[32];
	unsigned int affinity;
	unsigned int stack;
	unsigned int priority;
} pthread_attr_t_;

typedef SceUID pthread_t;
typedef struct pthread_attr_t_ * pthread_attr_t;

pthread_attr_t_ s_attr;

EXPORT pthread_t pthread_self(void)
{
	return sceKernelGetThreadId();
}

EXPORT int pthread_attr_init(pthread_attr_t *attr)
{
	sceClibMemset(&s_attr, 0, sizeof(pthread_attr_t_));
	*attr = &s_attr;
	return 0;
}

EXPORT int pthread_attr_destroy(pthread_attr_t *attr)
{
	return 0;
}

EXPORT int pthread_attr_setname_np(pthread_attr_t *attr, const char *name)
{
	sceClibStrncpy(s_attr.name, name, sizeof(s_attr.name));
	return 0;
}

EXPORT int pthread_attr_setaffinity_ext(pthread_attr_t *attr, unsigned int affinity)
{
	s_attr.affinity = affinity;
	return 0;
}

EXPORT int pthread_attr_setdetachstate(pthread_attr_t *attr, int state)
{
	//All FMOD threads are detached
	return 0;
}

EXPORT int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
	s_attr.stack = stacksize;
	return 0;
}

EXPORT int pthread_attr_setschedparam(pthread_attr_t *attr, sched_param *param)
{
	s_attr.priority = param->sched_priority;
	return 0;
}

SceInt32 pthreadEntry(SceSize argSize, void *pArgBlock)
{
	pthreadEntryArg *arg = (pthreadEntryArg *)pArgBlock;
	arg->func(arg->arg);
	sceKernelExitDeleteThread(0);
}

EXPORT int pthread_create(pthread_t *thread,
	const pthread_attr_t *attr,
	void *(*start)(void *),
	void *param)
{
	SceUID id;
	pthreadEntryArg arg;

	id = sceKernelCreateThread(s_attr.name, pthreadEntry, s_attr.priority, s_attr.stack, 0, s_attr.affinity, NULL);
	if (id <= 0) {
		return -1;
	}

	arg.func = start;
	arg.arg = param;

	sceKernelStartThread(id, sizeof(pthreadEntryArg), &arg);

	*thread = id;

	return 0;
}