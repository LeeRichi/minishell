/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:42:54 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/11 15:57:59 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_start;
	t_list	*tmp_node;
	void	*new_content;

	new_list_start = 0;
	tmp_node = 0;
	new_content = 0;
	if (!f || !del)
		return (0);
	while (lst)
	{
		new_content = f(lst->content);
		tmp_node = ft_lstnew(new_content);
		if (!tmp_node)
		{
			del(new_content);
			ft_lstclear(&new_list_start, del);
			return (0);
		}
		ft_lstadd_back(&new_list_start, tmp_node);
		lst = lst->next;
	}
	return (new_list_start);
}
