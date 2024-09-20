/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lag.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:20:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/20 12:19:49 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAG_H
# define LAG_H

# include "./vec4_la_ps/vec4s_linear_algebra.h"
# include "./vec4_la_pd/vec4_linear_algebra.h"
# include "./mat4_la_ps/mat4s_linear_algebra.h"

/*--- Matrix 4x4 ---*/

// @brief 
void	lag_mat4_cross(const t_mat4d *in, const t_mat4d *in2, t_mat4d *out);

#endif // !LAG_H