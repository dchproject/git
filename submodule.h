#ifndef SUBMODULE_H
#define SUBMODULE_H

struct diff_options;
struct argv_array;

enum {
	RECURSE_SUBMODULES_CHECK = -4,
	RECURSE_SUBMODULES_ERROR = -3,
	RECURSE_SUBMODULES_NONE = -2,
	RECURSE_SUBMODULES_ON_DEMAND = -1,
	RECURSE_SUBMODULES_OFF = 0,
	RECURSE_SUBMODULES_DEFAULT = 1,
	RECURSE_SUBMODULES_ON = 2
};

enum submodule_update_type {
	SM_UPDATE_UNSPECIFIED = 0,
	SM_UPDATE_CHECKOUT,
	SM_UPDATE_REBASE,
	SM_UPDATE_MERGE,
	SM_UPDATE_NONE,
	SM_UPDATE_COMMAND
};

struct submodule_update_strategy {
	enum submodule_update_type type;
	const char *command;
};
#define SUBMODULE_UPDATE_STRATEGY_INIT {SM_UPDATE_UNSPECIFIED, NULL}

extern int is_staging_gitmodules_ok(void);
extern int update_path_in_gitmodules(const char *oldpath, const char *newpath);
extern int remove_path_from_gitmodules(const char *path);
extern void stage_updated_gitmodules(void);
extern void set_diffopt_flags_from_submodule_config(struct diff_options *,
		const char *path);
extern int submodule_config(const char *var, const char *value, void *cb);
extern void gitmodules_config(void);
extern int parse_submodule_update_strategy(const char *value,
		struct submodule_update_strategy *dst);
extern const char *submodule_strategy_to_string(const struct submodule_update_strategy *s);
extern void handle_ignore_submodules_arg(struct diff_options *, const char *);
extern void show_submodule_summary(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset);
extern void show_submodule_inline_diff(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset,
		const struct diff_options *opt);
extern void set_config_fetch_recurse_submodules(int value);
extern void check_for_new_submodule_commits(unsigned char new_sha1[20]);
extern int fetch_populated_submodules(const struct argv_array *options,
			       const char *prefix, int command_line_option,
			       int quiet, int max_parallel_jobs);
extern unsigned is_submodule_modified(const char *path, int ignore_untracked);
extern int submodule_uses_gitfile(const char *path);
extern int ok_to_remove_submodule(const char *path);
extern int merge_submodule(unsigned char result[20], const char *path,
			   const unsigned char base[20],
			   const unsigned char a[20],
			   const unsigned char b[20], int search);
extern int find_unpushed_submodules(unsigned char new_sha1[20],
				    const char *remotes_name,
				    struct string_list *needs_pushing);
extern int push_unpushed_submodules(unsigned char new_sha1[20],
				    const char *remotes_name);
extern void connect_work_tree_and_git_dir(const char *work_tree, const char *git_dir);
extern int parallel_submodules(void);

/*
 * Prepare the "env_array" parameter of a "struct child_process" for executing
 * a submodule by clearing any repo-specific envirionment variables, but
 * retaining any config in the environment.
 */
extern void prepare_submodule_repo_env(struct argv_array *out);

#define ABSORB_GITDIR_RECURSE_SUBMODULES (1<<0)
extern void absorb_git_dir_into_superproject(const char *prefix,
					     const char *path,
					     unsigned flags);
#endif
